#include "StdAfx.h"

#include "Object Cache.h"
#include "IDisposable.h"

using namespace System::Collections::Generic;
using namespace StillDesign::PhysX;

void ObjectCache::Add( intptr_t pointer, Object^ object )
{
	if( IsInstanceOf<StillDesign::PhysX::IDisposable^>( object ) == true )
	{
		StillDesign::PhysX::IDisposable^ disposableObject = dynamic_cast<StillDesign::PhysX::IDisposable^>( object );
		
		disposableObject->OnDisposing += gcnew EventHandler( &ObjectCache::_cache_OnDisposing );
	}
	
	try
	{
		_cache->Add( pointer, object );
	}catch( Exception^ ex ){
		throw;
	}
}

bool ObjectCache::Remove( intptr_t pointer )
{
	Object^ object = _cache[ pointer ];
	
	if( IsInstanceOf<StillDesign::PhysX::IDisposable^>( object ) == true )
	{
		StillDesign::PhysX::IDisposable^ disposableObject = dynamic_cast<StillDesign::PhysX::IDisposable^>( object );
		
		disposableObject->OnDisposing -= gcnew EventHandler( &ObjectCache::_cache_OnDisposing );
	}
	
	return _cache->Remove( pointer );
}
bool ObjectCache::Remove( Object^ object )
{
	for each( KeyValuePair<intptr_t, Object^>^ pair in _cache )
	{
		if( pair->Value == object )
			return Remove( pair->Key );
	}
	
	return false;
}

void ObjectCache::Clear()
{
	_cache->Clear();
}

generic<class T>
T ObjectCache::GetObject( intptr_t pointer )
{
	return (T)_cache[ pointer ];
}

//generic<class T>
//T ObjectCache::GetObjectByIndexIfType( int index )
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
//array<T>^ ObjectCache::GetObjectsOfType()
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
//T ObjectCache::GetObjectOrNull( intptr_t pointer )
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

int ObjectCache::Count::get()
{
	return _cache->Count;
}

void ObjectCache::_cache_OnDisposing( Object^ sender, EventArgs^ e )
{
	Remove( sender );
}