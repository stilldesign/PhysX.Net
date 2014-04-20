#include "StdAfx.h"

#include "List Base.h"
#include "Read Only List.h"

using namespace System::Collections::ObjectModel;
using namespace StillDesign::PhysX;

generic<class T>
ListBase<T>::ListBase()
{
	_readOnlyCollection = gcnew ReadOnlyList<T>( this );
}

generic<class T>
ListBase<T>::ListBase( int capacity ) : Collection<T>( gcnew System::Collections::Generic::List<T>( capacity ) )
{
	_readOnlyCollection = gcnew ReadOnlyList<T>( this );
}
generic<class T>
ListBase<T>::ListBase( System::Collections::Generic::IEnumerable<T>^ collection ) : Collection<T>( CopyToList( collection ) )
{
	_readOnlyCollection = gcnew ReadOnlyList<T>( this );
}

generic<class T>
void ListBase<T>::RaiseAdd( T item )
{
	ItemAdded( this, item );
}
generic<class T>
void ListBase<T>::RaiseRemove( T item )
{
	ItemRemoved( this, item );
}

generic<class T>
List<T>^ ListBase<T>::CopyToList( System::Collections::Generic::IEnumerable<T>^ collection )
{
	List<T>^ list = gcnew List<T>();
	
	for each( T item in collection )
	{
		list->Add( item );
	}
	
	list->TrimExcess();
	
	return list;
}

generic<class T>
void ListBase<T>::ClearItems()
{
	int count = this->Count;
	
	for( int i = 0; i < count; i++ )
	{
		this->RemoveAt( 0 );
	}
}
generic<class T>
void ListBase<T>::InsertItem( int index, T item )
{
	RaiseAdd( item );
	
	System::Collections::ObjectModel::Collection<T>::InsertItem( index, item );
}
generic<class T>
void ListBase<T>::RemoveItem( int index )
{
	RaiseRemove( this[ index ] );
	
	System::Collections::ObjectModel::Collection<T>::RemoveItem( index );
}
generic<class T>
void ListBase<T>::SetItem( int index, T item )
{
	RaiseRemove( this[ index ] );
	
	System::Collections::ObjectModel::Collection<T>::SetItem( index, item );
	
	RaiseAdd( item );
}

generic<class T>
array<T>^ ListBase<T>::ToArray()
{
	array<T>^ a = gcnew array<T>( this->Count );
	for( int i = 0; i < this->Count; i++ )
	{
		a[ i ] = this[ i ];
	}
	
	return a;
}

generic<class T>
ReadOnlyList<T>^ ListBase<T>::ReadOnlyCollection::get()
{
	return _readOnlyCollection;
}