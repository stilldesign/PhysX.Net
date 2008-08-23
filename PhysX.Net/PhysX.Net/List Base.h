#pragma once

generic<class T>
public delegate void EventHandlerItem( Object^ sender, T item );

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace StillDesign
{
	namespace PhysX
	{
		generic<class T>
		public ref class ListBase abstract : 
			System::Collections::ICollection,
			System::Collections::Generic::ICollection<T>,
			System::Collections::IList,
			System::Collections::Generic::IList<T>,
			System::Collections::IEnumerable,
			System::Collections::Generic::IEnumerable<T>
		{
			public:
				/// <summary>Occurs when an Item is Added to the Collection</summary>
				event EventHandlerItem<T>^ onAdd;
				/// <summary>Occurs when an Item is Removed from the Collection</summary>
				event EventHandlerItem<T>^ onRemove;
			
			private:
				System::Collections::Generic::List<T>^ _collection;
			
			protected:
				void RaiseAdd( T item )
				{
					onAdd( this, item );
				}
				void RaiseRemove( T item )
				{
					onRemove( this, item );
				}
			
			public:
				ListBase()
				{
					_collection = gcnew System::Collections::Generic::List<T>();
				}
				ListBase( int capacity )
				{
					_collection = gcnew System::Collections::Generic::List<T>( capacity );
				}
				ListBase( System::Collections::Generic::IEnumerable<T>^ collection )
				{
					_collection = gcnew System::Collections::Generic::List<T>( collection );
				}

				/// <summary>Adds a New Item to the Collection</summary>
				/// <param name="item">The Item to Add</param>
				virtual void Add( T item )
				{
					_collection->Add( item );
					
					this->RaiseAdd( item );
				}
				virtual int Add( Object^ item ) = System::Collections::IList::Add
				{
					int index = ((System::Collections::IList^)_collection)->Add( item );
					
					this->RaiseAdd( (T)item );
					
					return index;
				}
				virtual void AddRange( System::Collections::Generic::IEnumerable<T>^ collection )
				{
					for each( T item in collection )
					{
						this->Add( item );
					}
				}
				virtual void AddRange( array<T>^ collection )
				{
					for each( T item in collection )
					{
						this->Add( item );
					}
				}
				virtual void Insert( int index, T item )
				{
					_collection->Insert( index, item );
					
					this->RaiseAdd( item );
				}
				void Insert( int index, System::Collections::Generic::IEnumerable<T>^ collection )
				{
					for each( T item in collection )
					{
						this->Insert( index++, item );
					}
				}
				virtual void Insert( int index, Object^ item ) = System::Collections::IList::Insert
				{
					((System::Collections::IList^)_collection)->Insert( index, item );
				}
				/// <summary>Removes an Item from the Collection</summary>
				/// <param name="item">The Item to Remove</param>
				/// <returns>True if the Item was Successfully Removed</returns>
				virtual bool Remove( T item )
				{
					bool result = _collection->Remove( item );
					
					this->RaiseRemove( item );
					
					return result;
				}
				virtual void Remove( Object^ item ) = System::Collections::IList::Remove
				{
					return ((System::Collections::IList^)_collection)->Remove( item );
				}
				virtual void RemoveAt( int index )
				{
					T item = _collection[ index ];
					
					_collection->RemoveAt( index );
					
					this->RaiseRemove( item );
				}
				virtual void RemoveRange( int startIndex, int length )
				{
					for( int x = 0; x < length; x++ )
					{
						this->RemoveAt( startIndex );
					}
				}
				/// <summary>Removes All Items from the Collection</summary>
				virtual void Clear()
				{
					int count = this->Count;
					for( int x = 0; x < count; x++ )
					{
						if( this->Count > 0 )
							this->RemoveAt( 0 );
					}
				}
					
			public:
				virtual int IndexOf( T item )
				{
					return this->IndexOf( item, 0, this->Count );
				}
				virtual int IndexOf( T item, int startIndex )
				{
					return this->IndexOf( item, startIndex, this->Count );
				}
				virtual int IndexOf( T item, int startIndex, int length )
				{
					return _collection->IndexOf( item, startIndex, length );
				}
				virtual int IndexOf( Object^ item ) = System::Collections::IList::IndexOf
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
				virtual bool Contains( T item )
				{
					return ( this->IndexOf( item ) != -1 );
				}
				virtual bool Contains( Object^ item ) = System::Collections::IList::Contains
				{
					return ((System::Collections::IList^)_collection)->Contains( item );
				}
				virtual bool Exists( Predicate<T>^ match )
				{
					return _collection->Exists( match );
				}
				virtual T Find( Predicate<T>^ match )
				{
					return _collection->Find( match );
				}
				virtual array<T>^ FindAll( Predicate<T>^ match )
				{
					return _collection->FindAll( match )->ToArray();
				}
				virtual int FindIndex( Predicate<T>^ match )
				{
					return _collection->FindIndex( match );
				}
				virtual int FindIndex( Predicate<T>^ match, int startIndex )
				{
					return _collection->FindIndex( startIndex, match );
				}
				virtual int FindIndex( Predicate<T>^ match, int startIndex, int length )
				{
					return _collection->FindIndex( startIndex, length, match );
				}
				virtual int FindLastIndex( Predicate<T>^ match )
				{
					return _collection->FindLastIndex( match );
				}
				virtual int FindLastIndex( Predicate<T>^ match, int startIndex )
				{
					return _collection->FindLastIndex( startIndex, match );
				}
				virtual int FindLastIndex( Predicate<T>^ match, int startIndex, int length )
				{
					return _collection->FindLastIndex( startIndex, length, match );
				}
				virtual int LastIndex( T item )
				{
					return _collection->LastIndexOf( item );
				}
				virtual int LastIndexOf( T item, int startIndex )
				{
					return _collection->LastIndexOf( item, startIndex );
				}
				virtual int LastIndexOf( T item, int startIndex, int length )
				{
					return _collection->LastIndexOf( item, startIndex, length );
				}

				virtual void ForEach( Action<T>^ action )
				{
					for each( T item in _collection )
					{
						action( item );
					}
				}
				virtual int BinarySearch( T item )
				{
					return _collection->BinarySearch( item );
				}
				virtual int BinarySearch( T item, System::Collections::Generic::IComparer<T>^ comparer )
				{
					return _collection->BinarySearch( item, comparer );
				}
				virtual int BinarySearch( T item, System::Collections::Generic::IComparer<T>^ comparer, int index, int length )
				{
					return _collection->BinarySearch( index, length, item, comparer );
				}
				bool TrueForAll( Predicate<T>^ match )
				{
					return _collection->TrueForAll( match );
				}
				
				virtual void CopyTo( Array^ a, int arrayIndex ) = System::Collections::ICollection::CopyTo
				{
					((System::Collections::ICollection^)_collection)->CopyTo( a, arrayIndex );
				}
				/// <summary>Copies the Contents of this List to an Array</summary>
				/// <param name="array">The Array to Copy the Elements in to</param>
				/// <param name="arrayIndex">The index to use as an Offset</param>
				virtual void CopyTo( array<T>^ a, int arrayIndex )
				{
					_collection->CopyTo( a, arrayIndex );
				}
				virtual void CopyTo( List<T>^ a )
				{
					for each( T item in this )
					{
						a->Add( item );
					}
				}
				virtual array<T>^ ToArray()
				{
					return _collection->ToArray();
				}
				virtual void TrimExcess()
				{
					_collection->TrimExcess();
				}
				virtual System::Collections::ObjectModel::ReadOnlyCollection<T>^ AsReadOnly()
				{
					return _collection->AsReadOnly();
				}
				generic<class TOutput>
				virtual System::Collections::Generic::List<TOutput>^ ConvertAll( Converter<T, TOutput>^ converter )
				{
					return _collection->ConvertAll<TOutput>( converter );
				}
				virtual System::Collections::Generic::List<T>^ GetRange( int startIndex, int length )
				{
					return _collection->GetRange( startIndex, length );
				}
				virtual void Reverse()
				{
					_collection->Reverse();
				}
				virtual void Reverse( int startIndex, int length )
				{
					_collection->Reverse( startIndex, length );
				}
				virtual void Sort()
				{
					_collection->Sort();
				}
				virtual void Sort( Comparison<T>^ comparison )
				{
					_collection->Sort( comparison );
				}
				virtual void Sort( System::Collections::Generic::IComparer<T>^ comparer, int startIndex, int length )
				{
					_collection->Sort( startIndex, length, comparer );
				}
				virtual void Sort( System::Collections::Generic::IComparer<T>^ comparer )
				{
					_collection->Sort( comparer );
				}
				
				virtual System::Collections::IEnumerator^ GetEnumerator1() = System::Collections::IEnumerable::GetEnumerator
				{
					return ((System::Collections::IList^)_collection)->GetEnumerator();
				}
				virtual System::Collections::Generic::IEnumerator<T>^ GetEnumerator2() = System::Collections::Generic::IEnumerable<T>::GetEnumerator
				{
					return ((System::Collections::Generic::IList<T>^)_collection)->GetEnumerator();
				}
				
				#pragma region Properties
					/// <summary>Gets the Count of Items in the Collection</summary>
					property int Count
					{
						virtual int get()
						{
							return _collection->Count;
						}
					}
					property int Capacity
					{
						virtual int get()
						{
							return _collection->Capacity;
						}
					}

					property bool IsReadOnly
					{
						virtual bool get()
						{
							return false;
						}
					}
					property bool IsFixedSize
					{
						virtual bool get()
						{
							return ((System::Collections::IList^)_collection)->IsFixedSize;
						}
					}

					property bool IsSynchronized
					{
						virtual bool get() = System::Collections::ICollection::IsSynchronized::get
						{
							return ((System::Collections::ICollection^)_collection)->IsSynchronized;
						}
					}
					property Object^ SyncRoot
					{
						virtual Object^ get()
						{
							return ((System::Collections::ICollection^)_collection)->SyncRoot;
						}
					}
					
					property Object^ default1[ int ]
					{
						virtual Object^ get( int index ) = System::Collections::IList::default::get
						{
							return _collection[ index ];
						}
						virtual void set( int index, Object^ value ) = System::Collections::IList::default::set
						{
							this->RaiseRemove( (T)_collection[ index ] );
							
							_collection[ index ] = (T)value;
							
							this->RaiseAdd( (T)_collection[ index ] );
						}
					}
					/// <summary>Gets or Sets the Item at The Index</summary>
					/// <param name="index">Index to Access</param>
					/// <returns>An Object of T</returns>
					property T default[ int ]
					{
						virtual T get( int index ) = System::Collections::Generic::IList<T>::default::get
						{
							return _collection[ index ];
						}
						virtual void set( int index, T value ) = System::Collections::Generic::IList<T>::default::set
						{
							this->RaiseRemove( _collection[ index ] );
							
							_collection[ index ] = value;
							
							this->RaiseAdd( _collection[ index ] );
						}
					}
		#pragma endregion
		};
	};
};