#include "StdAfx.h"

#include "List Base.h"

using namespace System::Collections::ObjectModel;
using namespace StillDesign::PhysX;

generic<class T>
ListBase<T>::ListBase()
{
	_readOnlyCollection = gcnew System::Collections::ObjectModel::ReadOnlyCollection< T >( Items );
}

generic<class T>
ListBase<T>::ListBase( int capacity ) : Collection<T>( gcnew System::Collections::Generic::List<T>( capacity ) )
{
	_readOnlyCollection = gcnew System::Collections::ObjectModel::ReadOnlyCollection< T >( Items );
}
//generic<class T>
//ListBase<T>::ListBase( System::Collections::Generic::IEnumerable<T>^ collection ) : System::Collections::ObjectModel::Collection<T>( collection )
//{
//	
//}

generic<class T>
void ListBase<T>::RaiseAdd( T item )
{
	onAdd( this, item );
}
generic<class T>
void ListBase<T>::RaiseRemove( T item )
{
	onRemove( this, item );
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

generic< class T >
System::Collections::ObjectModel::ReadOnlyCollection< T >^ ListBase< T >::ReadOnlyCollection::get()
{
	return _readOnlyCollection;
}