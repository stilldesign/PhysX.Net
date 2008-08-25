#include "StdAfx.h"

#include "List Base.h"

using namespace StillDesign::PhysX;

generic<class T>
ListBase::ListBase()
{
	_collection = gcnew System::Collections::Generic::List<T>();
}
generic<class T>
ListBase::ListBase( int capacity )
{
	_collection = gcnew System::Collections::Generic::List<T>( capacity );
}
generic<class T>
ListBase::ListBase( System::Collections::Generic::IEnumerable<T>^ collection )
{
	_collection = gcnew System::Collections::Generic::List<T>( collection );
}

/// <summary>Adds a New Item to the Collection</summary>
/// <param name="item">The Item to Add</param>
generic<class T>
void ListBase::Add( T item )
{
	_collection->Add( item );
	
	this->RaiseAdd( item );
}
generic<class T>
int ListBase::Add( Object^ item ) = System::Collections::IList::Add
{
	int index = ((System::Collections::IList^)_collection)->Add( item );
	
	this->RaiseAdd( (T)item );
	
	return index;
}
void ListBase::AddRange( System::Collections::Generic::IEnumerable<T>^ collection )
{
	for each( T item in collection )
	{
		this->Add( item );
	}
}
void ListBase::AddRange( array<T>^ collection )
{
	for each( T item in collection )
	{
		this->Add( item );
	}
}
void ListBase::Insert( int index, T item )
{
	_collection->Insert( index, item );
	
	this->RaiseAdd( item );
}
void ListBase::Insert( int index, System::Collections::Generic::IEnumerable<T>^ collection )
{
	for each( T item in collection )
	{
		this->Insert( index++, item );
	}
}
void ListBase::Insert( int index, Object^ item ) = System::Collections::IList::Insert
{
	((System::Collections::IList^)_collection)->Insert( index, item );
}
/// <summary>Removes an Item from the Collection</summary>
/// <param name="item">The Item to Remove</param>
/// <returns>True if the Item was Successfully Removed</returns>
bool ListBase::Remove( T item )
{
	bool result = _collection->Remove( item );
	
	this->RaiseRemove( item );
	
	return result;
}
void ListBase::Remove( Object^ item ) = System::Collections::IList::Remove
{
	return ((System::Collections::IList^)_collection)->Remove( item );
}
void ListBase::RemoveAt( int index )
{
	T item = _collection[ index ];
	
	_collection->RemoveAt( index );
	
	this->RaiseRemove( item );
}
void ListBase::RemoveRange( int startIndex, int length )
{
	for( int x = 0; x < length; x++ )
	{
		this->RemoveAt( startIndex );
	}
}
/// <summary>Removes All Items from the Collection</summary>
void ListBase::Clear()
{
	int count = this->Count;
	for( int x = 0; x < count; x++ )
	{
		if( this->Count > 0 )
			this->RemoveAt( 0 );
	}
}
	
public:
int ListBase::IndexOf( T item )
{
	return this->IndexOf( item, 0, this->Count );
}
int ListBase::IndexOf( T item, int startIndex )
{
	return this->IndexOf( item, startIndex, this->Count );
}
int ListBase::IndexOf( T item, int startIndex, int length )
{
	return _collection->IndexOf( item, startIndex, length );
}
int ListBase::IndexOf( Object^ item ) = System::Collections::IList::IndexOf
{
	return ((System::Collections::IList^)_collection)->IndexOf( item );
}
//virtual int IndexOf( Object^ item, int startIndex ) = System::Collections::IList::IndexOf
//{
//	return ((System::Collections::IList^)_collection)->IndexOf( item, startIndex );
//}
//virtual int IndexOf( Object^ item, int startIndex, int length ) = System::Collections::IList::IndexOf
//{
//	return ((System::Collections::IList^)_collection)->IndexOf( item, startIndex, length );
//}
bool ListBase::Contains( T item )
{
	return ( this->IndexOf( item ) != -1 );
}
bool ListBase::Contains( Object^ item ) = System::Collections::IList::Contains
{
	return ((System::Collections::IList^)_collection)->Contains( item );
}
bool ListBase::Exists( Predicate<T>^ match )
{
	return _collection->Exists( match );
}
T ListBase::Find( Predicate<T>^ match )
{
	return _collection->Find( match );
}
array<T>^ ListBase::FindAll( Predicate<T>^ match )
{
	return _collection->FindAll( match )->ToArray();
}
int ListBase::FindIndex( Predicate<T>^ match )
{
	return _collection->FindIndex( match );
}
int ListBase::FindIndex( Predicate<T>^ match, int startIndex )
{
	return _collection->FindIndex( startIndex, match );
}
int ListBase::FindIndex( Predicate<T>^ match, int startIndex, int length )
{
	return _collection->FindIndex( startIndex, length, match );
}
int ListBase::FindLastIndex( Predicate<T>^ match )
{
	return _collection->FindLastIndex( match );
}
int ListBase::FindLastIndex( Predicate<T>^ match, int startIndex )
{
	return _collection->FindLastIndex( startIndex, match );
}
int ListBase::FindLastIndex( Predicate<T>^ match, int startIndex, int length )
{
	return _collection->FindLastIndex( startIndex, length, match );
}
int ListBase::LastIndex( T item )
{
	return _collection->LastIndexOf( item );
}
int ListBase::LastIndexOf( T item, int startIndex )
{
	return _collection->LastIndexOf( item, startIndex );
}
int ListBase::LastIndexOf( T item, int startIndex, int length )
{
	return _collection->LastIndexOf( item, startIndex, length );
}

void ListBase::ForEach( Action<T>^ action )
{
	for each( T item in _collection )
	{
		action( item );
	}
}
int ListBase::BinarySearch( T item )
{
	return _collection->BinarySearch( item );
}
int ListBase::BinarySearch( T item, System::Collections::Generic::IComparer<T>^ comparer )
{
	return _collection->BinarySearch( item, comparer );
}
int ListBase::BinarySearch( T item, System::Collections::Generic::IComparer<T>^ comparer, int index, int length )
{
	return _collection->BinarySearch( index, length, item, comparer );
}
bool ListBase::TrueForAll( Predicate<T>^ match )
{
	return _collection->TrueForAll( match );
}

void ListBase::CopyTo( Array^ a, int arrayIndex ) = System::Collections::ICollection::CopyTo
{
	((System::Collections::ICollection^)_collection)->CopyTo( a, arrayIndex );
}
/// <summary>Copies the Contents of this List to an Array</summary>
/// <param name="array">The Array to Copy the Elements in to</param>
/// <param name="arrayIndex">The index to use as an Offset</param>
void ListBase::CopyTo( array<T>^ a, int arrayIndex )
{
	_collection->CopyTo( a, arrayIndex );
}
void ListBase::CopyTo( List<T>^ a )
{
	for each( T item in this )
	{
		a->Add( item );
	}
}
array<T>^ ListBase::ToArray()
{
	return _collection->ToArray();
}
void ListBase::TrimExcess()
{
	_collection->TrimExcess();
}
System::Collections::ObjectModel::ReadOnlyCollection<T>^ ListBase::AsReadOnly()
{
	return _collection->AsReadOnly();
}
generic<class TOutput>
System::Collections::Generic::List<TOutput>^ ListBase::ConvertAll( Converter<T, TOutput>^ converter )
{
	return _collection->ConvertAll<TOutput>( converter );
}
System::Collections::Generic::List<T>^ ListBase::GetRange( int startIndex, int length )
{
	return _collection->GetRange( startIndex, length );
}
void ListBase::Reverse()
{
	_collection->Reverse();
}
void ListBase::Reverse( int startIndex, int length )
{
	_collection->Reverse( startIndex, length );
}
void ListBase::Sort()
{
	_collection->Sort();
}
void ListBase::Sort( Comparison<T>^ comparison )
{
	_collection->Sort( comparison );
}
void ListBase::Sort( System::Collections::Generic::IComparer<T>^ comparer, int startIndex, int length )
{
	_collection->Sort( startIndex, length, comparer );
}
void ListBase::Sort( System::Collections::Generic::IComparer<T>^ comparer )
{
	_collection->Sort( comparer );
}

System::Collections::IEnumerator^ ListBase::GetEnumerator1() = System::Collections::IEnumerable::GetEnumerator
{
	return ((System::Collections::IList^)_collection)->GetEnumerator();
}
System::Collections::Generic::IEnumerator<T>^ ListBase::GetEnumerator2() = System::Collections::Generic::IEnumerable<T>::GetEnumerator
{
	return ((System::Collections::Generic::IList<T>^)_collection)->GetEnumerator();
}

#pragma region Properties
	/// <summary>Gets the Count of Items in the Collection</summary>
	int ListBase::Count::get()
	{
		return _collection->Count;
	}
	int ListBase::Capacity::get()
	{
		return _collection->Capacity;
	}
	
	property bool ListBase::IsReadOnly::get()
	{
		return false;
	}
	property bool ListBase::IsFixedSize::get()
	{
		return ((System::Collections::IList^)_collection)->IsFixedSize;
	}
	
	property bool ListBase::IsSynchronized::get() = System::Collections::ICollection::IsSynchronized::get
	{
		return ((System::Collections::ICollection^)_collection)->IsSynchronized;
	}
	property Object^ ListBase::SyncRoot::get()
	{
		return ((System::Collections::ICollection^)_collection)->SyncRoot;
	}
	
	property Object^ ListBase::default1::get( int index ) = System::Collections::IList::default::get
	{
		return _collection[ index ];
	}
	virtual void ListBase::default1::set( int index, Object^ value ) = System::Collections::IList::default::set
	{
		this->RaiseRemove( (T)_collection[ index ] );
		
		_collection[ index ] = (T)value;
		
		this->RaiseAdd( (T)_collection[ index ] );
	}
	/// <summary>Gets or Sets the Item at The Index</summary>
	/// <param name="index">Index to Access</param>
	/// <returns>An Object of T</returns>
	property T ListBase::default::get( int index ) = System::Collections::Generic::IList<T>::default::get
	{
		return _collection[ index ];
	}
	void ListBase::default::set( int index, T value ) = System::Collections::Generic::IList<T>::default::set
	{
		this->RaiseRemove( _collection[ index ] );
		
		_collection[ index ] = value;
		
		this->RaiseAdd( _collection[ index ] );
	}
#pragma endregion