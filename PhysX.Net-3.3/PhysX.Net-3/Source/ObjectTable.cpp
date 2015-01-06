#include "StdAfx.h"
#include "ObjectTable.h"
#include "IDisposable.h"
#include "PhysXException.h"

using namespace System::Threading;
using namespace System::Linq;

ObjectTable::ObjectTable()
{

}

// Add
generic<typename T>
void ObjectTable::Add(intptr_t pointer, T object, PhysX::IDisposable^ owner)
{
	Monitor::Enter(locker);
	try
	{
		if (pointer == NULL)
			throw gcnew PhysXException("Invalid pointer added to Object Table", "object");
		if (object == nullptr)
			throw gcnew ArgumentNullException("Invalid pointer added to Object Table", "owner");

		// Make sure we have not constructed a new managed object around an unmanaged pointer more than once
		// This leads to a case where one of the objects will be disposed, and the other(s) unaware of this and thus
		// holding on to broken pointers.
		// Unmanaged objects should only be wrapped once, then retrieved from the ObjectTable each time after.
		EnsureUnmanagedObjectIsOnlyWrappedOnce(pointer, object->GetType());

		AddObjectOwner(object, owner);
		AddOwnerTypeLookup<T>(owner, object);

		try
		{
			_objectTable->Add(pointer, object);
		}
		catch (Exception^)
		{
			throw;
		}
	}
	finally { Monitor::Exit(locker); }

	//raise event
	ObjectAdded(nullptr, gcnew ObjectTableEventArgs(pointer, object));
}

void ObjectTable::AddObjectOwner(PhysX::IDisposable^ object, PhysX::IDisposable^ owner)
{
	Monitor::Enter(locker);
	try
	{
		if (object == nullptr)
			throw gcnew ArgumentNullException("object");

		object->OnDisposing += gcnew EventHandler(&ObjectTable::disposableObject_OnDisposing);

		_ownership->Add(object, owner);
	}
	finally { Monitor::Exit(locker); }
}
generic<typename T>
void ObjectTable::AddOwnerTypeLookup(Object^ owner, T object)
{
	Monitor::Enter(locker);
	try
	{
		if (object == nullptr)
			throw gcnew ArgumentNullException("object");

		Type^ type = T::typeid;

		auto key = ObjectTableOwnershipType(owner, type);

		if (!_ownerTypeLookup->ContainsKey(key))
		{
			_ownerTypeLookup->Add(key, gcnew List<Object^>());
		}

		_ownerTypeLookup[key]->Add(object);
	}
	finally { Monitor::Exit(locker); }
}

void ObjectTable::EnsureUnmanagedObjectIsOnlyWrappedOnce(intptr_t unmanaged, Type^ managedType)
{
	Monitor::Enter(locker);
	try
	{
		if (!_objectTable->ContainsKey(unmanaged))
			return;

		auto obj = _objectTable[unmanaged];

		if (obj->GetType() == managedType)
			throw gcnew InvalidOperationException(String::Format("There is already a managed instance of type '{0}' wrapping this unmanaged object. Instead, retrieve the managed object from the ObjectTable using the unmanaged pointer as the lookup key.", managedType->FullName));
	}
	finally { Monitor::Exit(locker); }
}

// Remove
bool ObjectTable::Remove(intptr_t pointer)
{
	Object^ object = nullptr;
	bool result = false;

	Monitor::Enter(locker);
	try
	{
		//try get object
		if (_objectTable->TryGetValue(pointer, object) == false)
			return false; //does not exist

		// Unbind the OnDisposing event
		if (IsInstanceOf<PhysX::IDisposable^>(object))
		{
			IDisposable^ disposableObject = dynamic_cast<PhysX::IDisposable^>(object);

			disposableObject->OnDisposing -= gcnew EventHandler(&ObjectTable::disposableObject_OnDisposing);
		}

		// Remove from the pointer-object dictionary
		result = _objectTable->Remove(pointer);

		// Remove the from owner-type dictionary
		if (IsInstanceOf<PhysX::IDisposable^>(object))
		{
			IDisposable^ disposableObject = dynamic_cast<PhysX::IDisposable^>(object);

			IDisposable^ owner = _ownership[disposableObject];

			auto ownerTypeKey = ObjectTableOwnershipType(owner, object->GetType());

			if (_ownerTypeLookup->ContainsKey(ownerTypeKey))
			{
				_ownerTypeLookup[ownerTypeKey]->Remove(object);

				if (_ownerTypeLookup[ownerTypeKey]->Count == 0)
					_ownerTypeLookup->Remove(ownerTypeKey);
			}
		}

		// Remove from the ownership dictionary
		if (IsInstanceOf<PhysX::IDisposable^>(object))
		{
			IDisposable^ disposableObject = dynamic_cast<PhysX::IDisposable^>(object);

			_ownership->Remove(disposableObject);
		}
	}
	finally { Monitor::Exit(locker); }

	// Raise event
	ObjectRemoved(nullptr, gcnew ObjectTableEventArgs(pointer, object));

	return result;
}
bool ObjectTable::Remove(Object^ object)
{
	intptr_t key = (intptr_t)0;
	bool found = false;

	Monitor::Enter(locker);
	try
	{
		for each(KeyValuePair<intptr_t, Object^>^ pair in _objectTable)
			if (pair->Value == object)
			{
				key = pair->Key;
				found = true;
				break;
			}
	}
	finally { Monitor::Exit(locker); }

	if (found)
		return Remove(key);
	else
		return false;
}

void ObjectTable::Clear()
{
	Monitor::Enter(locker);
	try
	{
		_objectTable->Clear();
		_ownership->Clear();
		_ownerTypeLookup->Clear();
	}
	finally { Monitor::Exit(locker); }
}

//

int ObjectTable::Count::get()
{
	Monitor::Enter(locker);
	try
	{
		return _objectTable->Count;
	}
	finally { Monitor::Exit(locker); }
}

Dictionary<intptr_t, Object^>^ ObjectTable::Objects::get()
{
	return _objectTable;
}
Dictionary<PhysX::IDisposable^, PhysX::IDisposable^>^ ObjectTable::Ownership::get()
{
	return _ownership;
}
Dictionary<ObjectTableOwnershipType, List<Object^>^>^ ObjectTable::OwnerTypeLookup::get()
{
	return _ownerTypeLookup;
}