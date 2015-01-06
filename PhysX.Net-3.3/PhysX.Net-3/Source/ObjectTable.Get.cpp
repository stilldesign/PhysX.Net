#include "StdAfx.h"
#include "ObjectTable.h"
#include "IDisposable.h"
#include "PhysXException.h"

using namespace System::Threading;
using namespace System::Linq;

Object^ ObjectTable::GetObject(intptr_t pointer)
{
	return GetObject<Object^>(pointer);
}
generic<typename T>
T ObjectTable::GetObject(intptr_t pointer)
{
	Monitor::Enter(locker);
	try
	{
		// Gracefully handle code requesting NULL by returning managed null
		// This saves having to null check everywhere, as you can't add inptr_t NULL as the key for an
		// object to the ObjectTable in the first place
		if (pointer == NULL)
			return T();

		if (!_objectTable->ContainsKey(pointer))
			throw gcnew ArgumentException(String::Format("Cannot find managed object with pointer address '{0}' (of type '{1}')", pointer, T::typeid->FullName));

		return (T)_objectTable[pointer];
	}
	finally { Monitor::Exit(locker); }
}

Object^ ObjectTable::TryGetObject(intptr_t pointer)
{
	Monitor::Enter(locker);
	try
	{
		return TryGetObject<Object^>(pointer);
	}
	finally { Monitor::Exit(locker); }
}
generic<typename T>
T ObjectTable::TryGetObject(intptr_t pointer)
{
	Monitor::Enter(locker);
	try
	{
		if (!_objectTable->ContainsKey(pointer))
			return T(); // aka. default(T) We only store reference objects, so return nullptr.

		return (T)_objectTable[pointer];
	}
	finally { Monitor::Exit(locker); }
}

intptr_t ObjectTable::GetObject(Object^ object)
{
	Monitor::Enter(locker);
	try
	{
		for each(KeyValuePair<intptr_t, Object^> pair in _objectTable)
		{
			if (pair.Value == object)
			{
				return pair.Key;
			}
		}

		throw gcnew ArgumentException("Cannot find the unmanaged object");
	}
	finally { Monitor::Exit(locker); }
}

generic<typename T>
array<T>^ ObjectTable::GetObjects(intptr_t* pointers, int count)
{
	Monitor::Enter(locker);
	try
	{
		array<T>^ objects = gcnew array<T>(count);

		for (int i = 0; i < count; i++)
		{
			objects[i] = (T)_objectTable[pointers[i]];
		}

		return objects;
	}
	finally { Monitor::Exit(locker); }
}

generic<typename T>
array<T>^ ObjectTable::GetObjectsOfType()
{
	Monitor::Enter(locker);
	try
	{
		auto objects = gcnew List<T>();

		for each (Object^ obj in _objectTable->Values)
		{
			if (obj == nullptr)
				continue;

			if (obj->GetType() == T::typeid)
				objects->Add((T)obj);
		}

		return objects->ToArray();
	}
	finally { Monitor::Exit(locker); }
}
generic<typename T>
IEnumerable<T>^ ObjectTable::GetObjectsOfOwnerAndType(Object^ owner)
{
	Monitor::Enter(locker);
	try
	{
		ThrowIfNull(owner, "owner");

		auto key = ObjectTableOwnershipType(owner, T::typeid);

		if (!_ownerTypeLookup->ContainsKey(key))
			return gcnew array<T>(0);

		auto items = _ownerTypeLookup[key];

		return Enumerable::ToArray(Enumerable::Cast<T>(items));
	}
	finally { Monitor::Exit(locker); }
}

bool ObjectTable::Contains(intptr_t pointer)
{
	Monitor::Enter(locker);
	try
	{
		return _objectTable->ContainsKey(pointer);
	}
	finally { Monitor::Exit(locker); }
}
bool ObjectTable::Contains(Object^ object)
{
	Monitor::Enter(locker);
	try
	{
		return _objectTable->ContainsValue(object);
	}
	finally { Monitor::Exit(locker); }
}