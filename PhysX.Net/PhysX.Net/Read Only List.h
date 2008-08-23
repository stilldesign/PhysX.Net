#pragma once

#include "List Base.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace StillDesign
{
	namespace PhysX
	{
		generic<class T>
		public ref class ReadOnlyList : 
			System::Collections::IEnumerable, 
			System::Collections::Generic::IEnumerable<T>
		{
			public:
				/// <summary>Occurs when an Item is Added to the Collection</summary>
				event EventHandlerItem<T>^ onAdd;
				/// <summary>Occurs when an Item is Removed from the Collection</summary>
				event EventHandlerItem<T>^ onRemove;
				
			private:
				ListBase<T>^ _collection;
				
			public:
				ReadOnlyList()
				{
					
				}
				ReadOnlyList( ListBase<T>^ list )
				{
		#if DEBUG
					if( list == null )
						throw new ArgumentNullException( "list" );
		#endif

					_collection = list;
				}

				virtual void SetCollection( ListBase<T>^ collection )
				{
					if( _collection != nullptr )
						throw gcnew InvalidOperationException( "Collection Already Set" );

					_collection = collection;
				}
			
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
				virtual bool Contains( T item )
				{
					return _collection->Contains( item );
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
					return _collection->FindAll( match );
				}
				virtual int FindIndex( Predicate<T>^ match )
				{
					return _collection->FindIndex( match );
				}
				virtual int FindIndex( Predicate<T>^ match, int startIndex )
				{	
					return _collection->FindIndex( match, startIndex );
				}
				virtual int FindIndex( Predicate<T>^ match, int startIndex, int length )
				{
					return _collection->FindIndex( match, startIndex, length );
				}
				virtual int FindLastIndex( Predicate<T>^ match )
				{
					return _collection->FindLastIndex( match );
				}
				virtual int FindLastIndex( Predicate<T>^ match, int startIndex )
				{
					return _collection->FindLastIndex( match, startIndex );
				}
				virtual int FindLastIndex( Predicate<T>^ match, int startIndex, int length )
				{
					return _collection->FindLastIndex( match, startIndex, length );
				}
				virtual int LastIndex( T item )
				{
					return _collection->LastIndexOf( item, 0 );
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
					return _collection->BinarySearch( item, comparer, index, length );
				}
				bool TrueForAll( Predicate<T>^ match )
				{
					return _collection->TrueForAll( match );
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
				generic<class TOutput>
				virtual System::Collections::Generic::List<TOutput>^ ConvertAll( Converter<T, TOutput>^ converter )
				{
					return _collection->ConvertAll<TOutput>( converter );
				}
				virtual System::Collections::Generic::List<T>^ GetRange( int startIndex, int length )
				{
					return _collection->GetRange( startIndex, length );
				}
				
				virtual System::Collections::IEnumerator^ GetEnumerator1() = System::Collections::IEnumerable::GetEnumerator
				{
					return ((System::Collections::IEnumerable^)_collection)->GetEnumerator();
				}
				virtual System::Collections::Generic::IEnumerator<T>^ GetEnumerator2() = System::Collections::Generic::IEnumerable<T>::GetEnumerator
				{
					return ((System::Collections::Generic::IEnumerable<T>^)_collection)->GetEnumerator();
				}
				
				#pragma region Properties
				protected:
					property ListBase<T>^ Collection
					{
						ListBase<T>^ get()
						{
							return _collection;
						}
					}
					
				public:
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
						virtual bool get()
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
					
					/// <summary>Gets or Sets the Item at The Index</summary>
					/// <param name="index">Index to Access</param>
					/// <returns>An Object of T</returns>
					property T default[ int ]
					{
						virtual T get( int index )
						{
							return _collection->default[ index ];
						}
					}
				#pragma endregion
		};
	};
};