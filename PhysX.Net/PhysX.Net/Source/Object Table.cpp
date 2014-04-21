#include "StdAfx.h"

#include "Object Table.h"
#include "IDisposable.h"

using namespace System::Threading;
using namespace System::Collections::Generic;

using namespace StillDesign::PhysX;

void StillDesign::PhysX::ObjectTable::Add( intptr_t pointer, Object^ object )
{
	Add( pointer, object, nullptr );
}
void StillDesign::PhysX::ObjectTable::Add( intptr_t pointer, Object^ object, Object^ owner )
{
	if( pointer == NULL )
		throw gcnew PhysXException( "Invalid pointer added to Object Table", "pointer" );
	if( object == nullptr )
		throw gcnew ArgumentNullException( "Invalid pointer added to Object Table", "pointer" );
	
	Monitor::Enter( _syncObject );
	try
	{
		if( IsInstanceOf<StillDesign::PhysX::IDisposable^>( object ) == true )
		{
			StillDesign::PhysX::IDisposable^ disposableObject = dynamic_cast<StillDesign::PhysX::IDisposable^>( object );
			
			disposableObject->OnDisposing += gcnew EventHandler( &ObjectTable::_objectTable_OnDisposing );
		}
		
		try
		{
			_objectTable->Add( pointer, object );
			
			if( owner != nullptr )
				AddOwnership( object, owner );
			
			ObjectAdded( nullptr, gcnew ObjectTableEventArgs( pointer, object ) );
		}catch( Exception^ ){
			throw;
		}
	}finally{
		Monitor::Exit( _syncObject );
	}
}

bool StillDesign::PhysX::ObjectTable::Remove( intptr_t pointer )
{
	Monitor::Enter( _syncObject );
	try
	{
		Object^ object = _objectTable[ pointer ];
		
		if( IsInstanceOf<StillDesign::PhysX::IDisposable^>( object ) == true )
		{
			StillDesign::PhysX::IDisposable^ disposableObject = dynamic_cast<StillDesign::PhysX::IDisposable^>( object );
			
			disposableObject->OnDisposing -= gcnew EventHandler( &ObjectTable::_objectTable_OnDisposing );
		}
		
		bool result = _objectTable->Remove( pointer );
		
		if( _ownership->ContainsKey( object ) == true )
		{
			for each( Object^ ownershipObject in _ownership[ object ] )
			{
				_objectTable->Remove( GetObject( ownershipObject ) );
			}
			_ownership->Remove( object );
		}
		
		ObjectRemoved( nullptr, gcnew ObjectTableEventArgs( pointer, object ) );
		
		return result;
	}finally{
		Monitor::Exit( _syncObject );
	}
}
bool StillDesign::PhysX::ObjectTable::Remove( Object^ object )
{
	Monitor::Enter( _syncObject );
	try
	{
		for each( KeyValuePair<intptr_t, Object^>^ pair in _objectTable )
		{
			if( pair->Value == object )
				return Remove( pair->Key );
		}
		
		return false;
	}finally{
		Monitor::Exit( _syncObject );
	}
}

void StillDesign::PhysX::ObjectTable::Clear()
{
	Monitor::Enter( _syncObject );
	try
	{
		_objectTable->Clear();
	}finally{
		Monitor::Exit( _syncObject );
	}
}

generic<class T>
T StillDesign::PhysX::ObjectTable::GetObject( intptr_t pointer )
{
	Monitor::Enter( _syncObject );
	try
	{
		return (T)_objectTable[ pointer ];
	}finally{
		Monitor::Exit( _syncObject );
	}
}
intptr_t StillDesign::PhysX::ObjectTable::GetObject( Object^ object )
{
	Monitor::Enter( _syncObject );
	try
	{
		for each( KeyValuePair<intptr_t, Object^>^ pair in _objectTable )
		{
			if( pair->Value == object )
			{
				return pair->Key;
			}
		}
		
		throw gcnew Exception( "Unable to find object" );
	}finally{
		Monitor::Exit( _syncObject );
	}
}

bool StillDesign::PhysX::ObjectTable::Contains( intptr_t pointer )
{
	Monitor::Enter( _syncObject );
	try
	{
		return _objectTable->ContainsKey( pointer );
	}finally{
		Monitor::Exit( _syncObject );
	}
}

void StillDesign::PhysX::ObjectTable::AddOwnership( Object^ object, Object^ owner )
{
	if( object == nullptr )
		throw gcnew ArgumentNullException( "object" );
	if( owner == nullptr )
		throw gcnew ArgumentNullException( "owner" );
	
	//Monitor::Enter( _syncObject );
	//try
	//{
	
	if( _ownership->ContainsKey( owner ) == false )
	{
		_ownership->Add( owner, gcnew OwnershipObjects() );
	}
	
	_ownership[ owner ]->Add( object );
	
	//}finally{
		//Monitor::Exit( _syncObject );
	//}
}

//generic<class T>
//T ObjectTable::GetObjectByIndexIfType( int index )
//{
//	intptr_t key = _objectTable->Keys[ index ];
//	
//	for each( intptr_t key in _objectTable->Keys )
//	{
//		
//	}
//	
//	return dynamic_cast<T>( _objectTable[ key ] );
//}
//generic<class T>
//array<T>^ ObjectTable::GetObjectsOfType()
//{
//	System::Collections::Generic::List<T>^ items = gcnew System::Collections::Generic::List<T>();
//	
//	for each( intptr_t key in _objectTable->Keys )
//	{
//		if( dynamic_cast<T>( _objectTable[ key ] ) != nullptr )
//		{
//			items->Add( _objectTable[ key ] );
//		}
//	}
//	
//	return items->ToArray();
//}

//generic<class T>
//T ObjectTable::GetObjectOrNull( intptr_t pointer )
//{
//	if( pointer == NULL )
//		return nullptr;
//	
//	Object^ obj;
//	
//	bool b = _objectTable->TryGetValue( pointer, obj );
//	
//	if( b == true )
//		return (T)obj;
//	else
//		return nullptr;
//}

int StillDesign::PhysX::ObjectTable::Count::get()
{
	Monitor::Enter( _syncObject );
	try
	{
		return _objectTable->Count;
	}finally{
		Monitor::Exit( _syncObject );
	}
}

void StillDesign::PhysX::ObjectTable::_objectTable_OnDisposing( Object^ sender, EventArgs^ e )
{
	Monitor::Enter( _syncObject );
	try
	{
		Remove( sender );
	}finally{
		Monitor::Exit( _syncObject );
	}
}