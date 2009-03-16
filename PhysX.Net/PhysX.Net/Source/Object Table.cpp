#include "StdAfx.h"

#include "Object Table.h"
#include "IDisposable.h"

using namespace System::Collections::Generic;
using namespace StillDesign::PhysX;

void StillDesign::PhysX::ObjectTable::Add( intptr_t pointer, Object^ object )
{
	if( IsInstanceOf<StillDesign::PhysX::IDisposable^>( object ) == true )
	{
		StillDesign::PhysX::IDisposable^ disposableObject = dynamic_cast<StillDesign::PhysX::IDisposable^>( object );
		
		disposableObject->OnDisposing += gcnew EventHandler( &ObjectTable::_cache_OnDisposing );
	}
	
	try
	{
		_cache->Add( pointer, object );
	}catch( Exception^ ex ){
		throw;
	}
}

bool StillDesign::PhysX::ObjectTable::Remove( intptr_t pointer )
{
	Object^ object = _cache[ pointer ];
	
	if( IsInstanceOf<StillDesign::PhysX::IDisposable^>( object ) == true )
	{
		StillDesign::PhysX::IDisposable^ disposableObject = dynamic_cast<StillDesign::PhysX::IDisposable^>( object );
		
		disposableObject->OnDisposing -= gcnew EventHandler( &ObjectTable::_cache_OnDisposing );
	}
	
	return _cache->Remove( pointer );
}
bool StillDesign::PhysX::ObjectTable::Remove( Object^ object )
{
	for each( KeyValuePair<intptr_t, Object^>^ pair in _cache )
	{
		if( pair->Value == object )
			return Remove( pair->Key );
	}
	
	return false;
}

void StillDesign::PhysX::ObjectTable::Clear()
{
	_cache->Clear();
}

generic<class T>
T StillDesign::PhysX::ObjectTable::GetObject( intptr_t pointer )
{
	return (T)_cache[ pointer ];
}

bool StillDesign::PhysX::ObjectTable::Contains( intptr_t pointer )
{
	return _cache->ContainsKey( pointer );
}

//generic<class T>
//T ObjectTable::GetObjectByIndexIfType( int index )
//{
//	intptr_t key = _cache->Keys[ index ];
//	
//	for each( intptr_t key in _cache->Keys )
//	{
//		
//	}
//	
//	return dynamic_cast<T>( _cache[ key ] );
//}
//generic<class T>
//array<T>^ ObjectTable::GetObjectsOfType()
//{
//	System::Collections::Generic::List<T>^ items = gcnew System::Collections::Generic::List<T>();
//	
//	for each( intptr_t key in _cache->Keys )
//	{
//		if( dynamic_cast<T>( _cache[ key ] ) != nullptr )
//		{
//			items->Add( _cache[ key ] );
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
//	bool b = _cache->TryGetValue( pointer, obj );
//	
//	if( b == true )
//		return (T)obj;
//	else
//		return nullptr;
//}

int StillDesign::PhysX::ObjectTable::Count::get()
{
	return _cache->Count;
}

void StillDesign::PhysX::ObjectTable::_cache_OnDisposing( Object^ sender, EventArgs^ e )
{
	Remove( sender );
}