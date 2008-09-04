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
		public ref class ListBase : System::Collections::ObjectModel::Collection<T>
		{
			public:
				/// <summary>Occurs when an Item is Added to the Collection</summary>
				event EventHandlerItem<T>^ onAdd;
				/// <summary>Occurs when an Item is Removed from the Collection</summary>
				event EventHandlerItem<T>^ onRemove;
				
			public:
				ListBase();
				ListBase( int capacity );
				//ListBase( System::Collections::Generic::IEnumerable<T>^ collection );
				
			protected:
				void RaiseAdd( T item );
				void RaiseRemove( T item );
				
			public:
				virtual void ClearItems() override;
				virtual void InsertItem( int index, T item ) override;
				virtual void RemoveItem( int index ) override;
				virtual void SetItem( int index, T item ) override;
				
				array<T>^ ToArray();

				property System::Collections::ObjectModel::ReadOnlyCollection< T >^ ReadOnlyCollection
				{
					System::Collections::ObjectModel::ReadOnlyCollection< T >^ get();
				}

		private:
			System::Collections::ObjectModel::ReadOnlyCollection< T >^ _readOnlyCollection;
		};

	};
};