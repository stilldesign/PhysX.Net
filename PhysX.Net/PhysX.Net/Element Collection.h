#pragma once

#include "IDisposable.h"
#include "List Base.h"

using namespace System::Runtime::InteropServices;

namespace StillDesign
{
	namespace PhysX
	{
		
		generic< class T >
			where T : ref class, StillDesign::PhysX::IDisposable
		public ref class ElementCollection : ListBase< T >
		{
			public:
				ElementCollection();
				
			internal:
				void DiposeOfAll();
				
			private:
				void ElementCollection_onAdd( System::Object^ sender, T item );
				void ElementCollection_onRemove( System::Object^ sender, T item );
				
				void Element_onDisposing( System::Object^ sender, EventArgs^ e );
		};

	};
};