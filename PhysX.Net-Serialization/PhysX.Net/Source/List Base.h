#pragma once

#include "Read Only List.h"
#include "Delegates.h"

using namespace System;
using namespace System::Collections;
using namespace System::Collections::Generic;

namespace StillDesign
{
	namespace PhysX
	{
		generic<class T>
		ref class ReadOnlyList;
		
		generic<class T>
		public ref class ListBase : System::Collections::ObjectModel::Collection<T>
		{
			public:
				/// <summary>Occurs when an Item is Added to the Collection</summary>
				event EventHandlerItem<T>^ ItemAdded;
				/// <summary>Occurs when an Item is Removed from the Collection</summary>
				event EventHandlerItem<T>^ ItemRemoved;
				
			private:
				ReadOnlyList<T>^ _readOnlyCollection;
				
			public:
				ListBase();
				ListBase( int capacity );
				ListBase( System::Collections::Generic::IEnumerable<T>^ collection );
				
			protected:
				virtual void RaiseAdd( T item );
				virtual void RaiseRemove( T item );
				
			private:
				List<T>^ CopyToList( System::Collections::Generic::IEnumerable<T>^ collection );
				
			public:
				virtual void ClearItems() override;
				virtual void InsertItem( int index, T item ) override;
				virtual void RemoveItem( int index ) override;
				virtual void SetItem( int index, T item ) override;
				
				array<T>^ ToArray();
				
				property ReadOnlyList<T>^ ReadOnlyCollection
				{
					ReadOnlyList<T>^ get();
				}
		};
	};
};