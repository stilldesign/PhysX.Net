#include "StdAfx.h"
#include "ObjectTable.h"
#include "IDisposable.h"
#include "PhysXException.h"

using namespace System::Threading;
using namespace System::Linq;

generic<typename T>
T ObjectTable::GetObject(intptr_t pointer)
{
	// Gracefully handle code requesting NULL by returning managed null
	// This saves having to null check everywhere, as you can't add inptr_t NULL as the key for an
	// object to the ObjectTable in the first place
	if (pointer == NULL)
		return T();

	Object^ obj;
	if (!_objectTable->TryGetValue(pointer, obj))
		throw gcnew ArgumentException(String::Format("Cannot find managed object with pointer address '{0}' (of type '{1}')", pointer, T::typeid->FullName));

	return (T)obj;
}

generic<typename T>
T ObjectTable::TryGetObject(intptr_t pointer)
{
	if (!_objectTable->ContainsKey(pointer))
		return T(); // aka. default(T) We only store reference objects, so return nullptr.
	
	return (T)_objectTable[pointer];
}

intptr_t ObjectTable::GetObject(Object^ object)
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
	auto objects = gcnew List<T>();

	for each (Object^ obj in _objectTable->Values)
	{
		if (obj == nullptr)
			continue;

		if (T::typeid->IsAssignableFrom(obj->GetType()))
			objects->Add((T)obj);
	}

	return objects->ToArray();
}
generic<typename T>
array<T>^ ObjectTable::GetObjectsOfOwnerAndType(Object^ owner)
{
	ThrowIfNull(owner, "owner");

	auto key = ObjectTableOwnershipType(owner, T::typeid);

	if (!_ownerTypeLookup->ContainsKey(key))
		return System::Array::Empty<T>();

	auto items = _ownerTypeLookup[key];

	auto typedItems = Enumerable::Cast<T>(items);

	return Enumerable::ToArray(typedItems);
}

bool ObjectTable::Contains(intptr_t pointer)
{
	return _objectTable->ContainsKey(pointer);
}
bool ObjectTable::Contains(Object^ object)
{
	return _objectTable->ContainsValue(object);
}