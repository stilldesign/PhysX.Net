#include "StdAfx.h"
#include "ObjectTable.h"
#include "IDisposable.h"
#include "PhysXException.h"

using namespace System::Threading;
using namespace System::Linq;

Object^ ObjectTable::GetObject(intptr_t pointer)
{
	if (!_objectTable->ContainsKey(pointer))
		throw gcnew ArgumentException(String::Format("Cannot find managed object with pointer '{0}'", pointer));

	return _objectTable[pointer];
}

generic<typename T>
T ObjectTable::GetObject(intptr_t pointer)
{
	if (!_objectTable->ContainsKey(pointer))
		throw gcnew ArgumentException(String::Format("Cannot find managed object with pointer '{0}'", pointer));
	
	return (T)_objectTable[pointer];
}
intptr_t ObjectTable::GetObject(Object^ object)
{
	for each(KeyValuePair<intptr_t, Object^>^ pair in _objectTable)
	{
		if (pair->Value == object)
		{
			return pair->Key;
		}
	}
		
	throw gcnew ArgumentException("Cannot find the unmanaged object");
}

generic<typename T>
array<T>^ ObjectTable::GetObjects(intptr_t* pointers, int count)
{
	array<T>^ objects = gcnew array<T>(count);

	for (int i = 0; i < count; i++)
	{
		objects[i] = (T)_objectTable[pointers[i]];
	}

	return objects;
}

generic<typename T>
array<T>^ ObjectTable::GetObjectsOfType()
{
	List<T>^ objects = gcnew List<T>();

	for each (Object^ obj in _objectTable->Values)
	{
		if (obj == nullptr)
			continue;

		if (obj->GetType() == T::typeid)
			objects->Add((T)obj);
	}

	return objects->ToArray();
}
generic<typename T>
IEnumerable<T>^ ObjectTable::GetObjectsOfOwnerAndType(Object^ owner)
{
	ThrowIfNull(owner, "owner");

	auto key = ObjectTableOwnershipType(owner, T::typeid);

	if (!_ownerTypeLookup->ContainsKey(key))
		return gcnew array<T>(0);

	auto items = _ownerTypeLookup[key];

	return Enumerable::ToArray(Enumerable::Cast<T>(items));
}

bool ObjectTable::Contains(intptr_t pointer)
{
	return _objectTable->ContainsKey(pointer);
}
bool ObjectTable::Contains(Object^ object)
{
	return _objectTable->ContainsValue(object);
}