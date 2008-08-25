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
				ListBase();
				ListBase( int capacity );
				ListBase( System::Collections::Generic::IEnumerable<T>^ collection );
				
				/// <summary>Adds a New Item to the Collection</summary>
				/// <param name="item">The Item to Add</param>
				virtual void Add( T item );
				virtual int Add( Object^ item ) = System::Collections::IList::Add;
				virtual void AddRange( System::Collections::Generic::IEnumerable<T>^ collection );
				virtual void AddRange( array<T>^ collection );
				virtual void Insert( int index, T item );
				void Insert( int index, System::Collections::Generic::IEnumerable<T>^ collection );
				virtual void Insert( int index, Object^ item ) = System::Collections::IList::Insert;
				/// <summary>Removes an Item from the Collection</summary>
				/// <param name="item">The Item to Remove</param>
				/// <returns>True if the Item was Successfully Removed</returns>
				virtual bool Remove( T item );
				virtual void Remove( Object^ item ) = System::Collections::IList::Remove;
				virtual void RemoveAt( int index );
				virtual void RemoveRange( int startIndex, int length );
				/// <summary>Removes All Items from the Collection</summary>
				virtual void Clear();
					
			public:
				virtual int IndexOf( T item );
				virtual int IndexOf( T item, int startIndex );
				virtual int IndexOf( T item, int startIndex, int length );
				virtual int IndexOf( Object^ item ) = System::Collections::IList::IndexOf;
				
				virtual bool Contains( T item );
				virtual bool Contains( Object^ item ) = System::Collections::IList::Contains;
				virtual bool Exists( Predicate<T>^ match );
				virtual T Find( Predicate<T>^ match );
				virtual array<T>^ FindAll( Predicate<T>^ match );

				virtual int FindIndex( Predicate<T>^ match );
				virtual int FindIndex( Predicate<T>^ match, int startIndex );
				virtual int FindIndex( Predicate<T>^ match, int startIndex, int length );
				virtual int FindLastIndex( Predicate<T>^ match );
				virtual int FindLastIndex( Predicate<T>^ match, int startIndex );
				virtual int FindLastIndex( Predicate<T>^ match, int startIndex, int length );
				virtual int LastIndex( T item );
				virtual int LastIndexOf( T item, int startIndex );
				virtual int LastIndexOf( T item, int startIndex, int length );

				virtual void ForEach( Action<T>^ action );
				virtual int BinarySearch( T item );
				virtual int BinarySearch( T item, System::Collections::Generic::IComparer<T>^ comparer );
				virtual int BinarySearch( T item, System::Collections::Generic::IComparer<T>^ comparer, int index, int length );
				bool TrueForAll( Predicate<T>^ match );
				
				virtual void CopyTo( Array^ a, int arrayIndex ) = System::Collections::ICollection::CopyTo;
				/// <summary>Copies the Contents of this List to an Array</summary>
				/// <param name="array">The Array to Copy the Elements in to</param>
				/// <param name="arrayIndex">The index to use as an Offset</param>
				virtual void CopyTo( array<T>^ a, int arrayIndex );
				virtual void CopyTo( List<T>^ a );
				virtual array<T>^ ToArray();
				virtual void TrimExcess();
				virtual System::Collections::ObjectModel::ReadOnlyCollection<T>^ AsReadOnly();
				generic<class TOutput>
				virtual System::Collections::Generic::List<TOutput>^ ConvertAll( Converter<T, TOutput>^ converter );
				virtual System::Collections::Generic::List<T>^ GetRange( int startIndex, int length );
				virtual void Reverse();
				virtual void Reverse( int startIndex, int length );
				virtual void Sort();
				virtual void Sort( Comparison<T>^ comparison );
				virtual void Sort( System::Collections::Generic::IComparer<T>^ comparer, int startIndex, int length );
				virtual void Sort( System::Collections::Generic::IComparer<T>^ comparer );
				
				virtual System::Collections::IEnumerator^ GetEnumerator1() = System::Collections::IEnumerable::GetEnumerator;
				virtual System::Collections::Generic::IEnumerator<T>^ GetEnumerator2() = System::Collections::Generic::IEnumerable<T>::GetEnumerator;
				
				#pragma region Properties
					/// <summary>Gets the Count of Items in the Collection</summary>
					property int Count
					{
						virtual int get();
					}
					property int Capacity
					{
						virtual int get();
					}

					property bool IsReadOnly
					{
						virtual bool get();
					}
					property bool IsFixedSize
					{
						virtual bool get();
					}

					property bool IsSynchronized
					{
						virtual bool get() = System::Collections::ICollection::IsSynchronized::get;
					}
					property Object^ SyncRoot
					{
						virtual Object^ get();
					}
					
					property Object^ default1[ int ]
					{
						virtual Object^ get( int index ) = System::Collections::IList::default::get;
						virtual void set( int index, Object^ value ) = System::Collections::IList::default::set;
					}
					/// <summary>Gets or Sets the Item at The Index</summary>
					/// <param name="index">Index to Access</param>
					/// <returns>An Object of T</returns>
					property T default[ int ]
					{
						virtual T get( int index ) = System::Collections::Generic::IList<T>::default::get;
						virtual void set( int index, T value ) = System::Collections::Generic::IList<T>::default::set;
					}
		#pragma endregion
		};
	};
};