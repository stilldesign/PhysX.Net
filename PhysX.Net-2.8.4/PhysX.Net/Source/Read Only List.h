#pragma once

#include "Delegates.h"

using namespace System::Collections::Generic;

namespace StillDesign
{
	namespace PhysX
	{
		generic<class T>
		ref class ListBase;
		
		generic<class T>
		public ref class ReadOnlyList : System::Collections::ObjectModel::ReadOnlyCollection<T>
		{
			public:
				event EventHandlerItem<T>^ ItemAdded;
				event EventHandlerItem<T>^ ItemRemoved;
				
				ReadOnlyList( ListBase<T>^ list );
				
			private:
				void ReadOnlyList_ItemAdded( Object^ sender, T item );
				void ReadOnlyList_ItemRemoved( Object^ sender, T item );
		};
	};
};