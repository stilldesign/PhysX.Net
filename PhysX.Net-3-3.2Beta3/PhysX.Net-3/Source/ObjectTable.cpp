#include "StdAfx.h"
#include "ObjectTable.h"
#include "IDisposable.h"
#include "PhysXException.h"

using namespace System::Threading;

void ObjectTable::Add(intptr_t pointer, PhysX::IDisposable^ object, PhysX::IDisposable^ owner)
{
	if (pointer == NULL)
		throw gcnew PhysXException("Invalid pointer added to Object Table", "pointer");
	if (object == nullptr)
		throw gcnew ArgumentNullException("Invalid pointer added to Object Table", "pointer");
	
	Monitor::Enter(_syncObject);
	try
	{
		object->OnDisposing += gcnew EventHandler(&ObjectTable::disposableObject_OnDisposing);

		_ownership->Add(object, owner);
		
		try
		{
			_objectTable->Add(pointer, object);
		}
		catch(Exception^)
		{
			throw;
		}

		ObjectAdded(nullptr, gcnew ObjectTableEventArgs(pointer, object));
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}

bool PhysX::ObjectTable::Remove(intptr_t pointer)
{
	Monitor::Enter(_syncObject);
	try
	{
		Object^ object = _objectTable[pointer];
		
		if (IsInstanceOf<PhysX::IDisposable^>(object))
		{
			IDisposable^ disposableObject = dynamic_cast<PhysX::IDisposable^>(object);
			
			// Unbind the OnDisposing event
			disposableObject->OnDisposing -= gcnew EventHandler(&ObjectTable::disposableObject_OnDisposing);
		}
		
		// Remove the table item
		bool result = _objectTable->Remove(pointer);
		
		ObjectRemoved(nullptr, gcnew ObjectTableEventArgs(pointer, object));
		
		return result;
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}
bool PhysX::ObjectTable::Remove(Object^ object)
{
	Monitor::Enter(_syncObject);
	try
	{
		for each(KeyValuePair<intptr_t, Object^>^ pair in _objectTable)
		{
			if(pair->Value == object)
				return Remove(pair->Key);
		}
		
		return false;
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}

void PhysX::ObjectTable::Clear()
{
	Monitor::Enter(_syncObject);
	try
	{
		_objectTable->Clear();
		_ownership->Clear();
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}

generic<typename T>
T PhysX::ObjectTable::GetObject(intptr_t pointer)
{
	Monitor::Enter(_syncObject);
	try
	{
		return (T)_objectTable[ pointer ];
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}
intptr_t PhysX::ObjectTable::GetObject(Object^ object)
{
	Monitor::Enter(_syncObject);
	try
	{
		for each(KeyValuePair<intptr_t, Object^>^ pair in _objectTable)
		{
			if(pair->Value == object)
			{
				return pair->Key;
			}
		}
		
		throw gcnew Exception("Unable to find object");
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
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

bool PhysX::ObjectTable::Contains(intptr_t pointer)
{
	Monitor::Enter(_syncObject);
	try
	{
		return _objectTable->ContainsKey(pointer);
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}
bool PhysX::ObjectTable::Contains(Object^ object)
{
	return _objectTable->ContainsValue(object);
}

int PhysX::ObjectTable::Count::get()
{
	Monitor::Enter(_syncObject);
	try
	{
		return _objectTable->Count;
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}

void PhysX::ObjectTable::disposableObject_OnDisposing(Object^ sender, EventArgs^ e)
{
	Monitor::Enter(_syncObject);
	try
	{
		DisposeOfObjectAndDependents(dynamic_cast<IDisposable^>(sender));

		Remove(sender);
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}

void PhysX::ObjectTable::DisposeOfObjectAndDependents(IDisposable^ disposable)
{
	if (disposable == nullptr || disposable->Disposed || !_ownership->ContainsKey(disposable))
		return;

	Monitor::Enter(_syncObject);
	try
	{
		List<IDisposable^>^ dependents = gcnew List<IDisposable^>();
		for each(KeyValuePair<IDisposable^, IDisposable^> d in _ownership)
		{
			// Get the object (child) of the disposable arg
			IDisposable^ dependent = d.Key;

			if (dependent == nullptr)
				continue;

			// Check the owner
			if (d.Value == disposable)
			{
				dependents->Add(dependent);
			}
		}

		// Dispose of the objects children first, then it
		for each(IDisposable^ dependent in dependents)
		{
			// Recurse through dependent children
			DisposeOfObjectAndDependents(dependent);
		}
		
		_ownership->Remove(disposable);
		
		delete disposable;
	}
	finally
	{
		Monitor::Exit(_syncObject);
	}
}