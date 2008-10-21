#include "StdAfx.h"

#include "Element Collection.h"

using namespace System;
using namespace StillDesign::PhysX;

//generic< class T >ReadOnlyElementCollection< T >::ReadOnlyElementCollection()
//{
//	this->onAdd += gcnew EventHandlerItem< T >( this, &ReadOnlyElementCollection::ReadOnlyElementCollection_onAdd );
//	this->onRemove += gcnew EventHandlerItem< T >( this, &ReadOnlyElementCollection::ReadOnlyElementCollection_onRemove );
//}
////generic< class T >ReadOnlyElementCollection< T >::~ReadOnlyElementCollection()
////{
////	this->!ReadOnlyElementCollection();
////}
////generic< class T >ReadOnlyElementCollection< T >::!ReadOnlyElementCollection()
////{
////	this->onAdd -= gcnew EventHandlerItem< T >( this, &ReadOnlyElementCollection::ReadOnlyElementCollection_onAdd );
////	this->onRemove -= gcnew EventHandlerItem< T >( this, &ReadOnlyElementCollection::ReadOnlyElementCollection_onRemove );
////}
//
//generic< class T >void ReadOnlyElementCollection< T >::ReadOnlyElementCollection_onAdd( System::Object^ sender, T item )
//{
//	item->onDisposing += gcnew EventHandler( this, &ReadOnlyElementCollection< T >::ReadOnlyElement_onDisposing );
//}
//generic< class T >void ReadOnlyElementCollection< T >::ReadOnlyElementCollection_onRemove( System::Object^ sender, T item )
//{
//	item->onDisposing -= gcnew EventHandler( this, &ReadOnlyElementCollection< T >::ReadOnlyElement_onDisposing );
//}
//
//generic< class T >void ReadOnlyElementCollection< T >::ReadOnlyElement_onDisposing( System::Object^ sender, EventArgs^ e )
//{
//	this->Items->Remove( (T)sender );
//}

//

generic< class T >
ElementCollection< T >::ElementCollection()
{
	this->ItemAdded += gcnew EventHandlerItem< T >( this, &ElementCollection::ElementCollection_onAdd );
	this->ItemRemoved += gcnew EventHandlerItem< T >( this, &ElementCollection::ElementCollection_onRemove );
}

//generic< class T, class R >ElementCollection< T, R >::!ElementCollection()
//{
//	this->onAdd -= gcnew EventHandlerItem< T >( this, &ElementCollection::ElementCollection_onAdd );
//	this->onRemove -= gcnew EventHandlerItem< T >( this, &ElementCollection::ElementCollection_onRemove );
//}
//generic< class T, class R >ElementCollection< T, R >::~ElementCollection()
//{
//	this->!ElementCollection();
//}

generic< class T >
void ElementCollection< T >::DiposeOfAll()
{
	array<StillDesign::PhysX::IDisposable^>^ items = gcnew array<StillDesign::PhysX::IDisposable^>( this->Count );
	
	for( int x = 0; x < this->Count; x++ )
	{
		items[ x ] = (StillDesign::PhysX::IDisposable^)this[ x ];
	}
	
	for each( StillDesign::PhysX::IDisposable^ d in items )
	{
		delete d;
	}
}

generic< class T >
void ElementCollection< T >::ElementCollection_onAdd( System::Object^ sender, T item )
{
	item->onDisposing += gcnew EventHandler( this, &ElementCollection< T >::Element_onDisposing );
}

generic< class T >
void ElementCollection< T >::ElementCollection_onRemove( System::Object^ sender, T item )
{
	item->onDisposing -= gcnew EventHandler( this, &ElementCollection< T >::Element_onDisposing );
}

generic< class T >
void ElementCollection< T >::Element_onDisposing( System::Object^ sender, EventArgs^ e )
{
	this->Remove( (T)sender );
}

//

//generic< class T >
//ReadOnlyElementDictionary<T>::ReadOnlyElementDictionary()
//{
//	_dictionary = gcnew Dictionary<intptr_t, T>();
//}
//
//generic< class T >
//void ReadOnlyElementDictionary<T>::OnAdd( Object^ sender, T item )
//{
//	intptr_t pointer = GetPointerFromElement( item );
//	
//	if( pointer == NULL )
//		throw gcnew NullReferenceException( "Pointer Returned is Null" );
//	
//	_dictionary->Add( pointer, item );
//}
//generic< class T >
//void ReadOnlyElementDictionary<T>::OnRemove( Object^ sender, T item )
//{
//	intptr_t pointer = GetPointerFromElement( item );
//	
//	if( pointer == NULL )
//		throw gcnew NullReferenceException( "Pointer Returned is Null" );
//	
//	_dictionary->Remove( pointer );
//}
//
//generic< class T >
//T ReadOnlyElementDictionary<T>::GetElementByPointer( intptr_t pointer )
//{
//	return _dictionary[ pointer ];
//}