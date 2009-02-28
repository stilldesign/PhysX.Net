#pragma once

#include "IDisposable.h"
#include "List Base.h"

using namespace System::Runtime::InteropServices;

namespace StillDesign
{
	namespace PhysX
	{
		interface class IDisposeOfChildren
		{
			virtual void DisposeOfAll();
		};
		
		generic<class T>
			where T : ref class, StillDesign::PhysX::IDisposable
		public ref class ElementCollection : ListBase<T>, IDisposeOfChildren
		{
			internal:
				ElementCollection();
				
			internal:
				virtual void DisposeOfAll() = IDisposeOfChildren::DisposeOfAll;	
				
			private:
				void ElementCollection_OnAdd( System::Object^ sender, T item );
				void ElementCollection_OnRemove( System::Object^ sender, T item );
				
				void Element_OnDisposing( System::Object^ sender, EventArgs^ e );
		};
	};
};