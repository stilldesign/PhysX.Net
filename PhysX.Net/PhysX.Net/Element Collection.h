#pragma once

#include "IDisposable.h"
#include "List.h"
#include "Read Only List.h"

using namespace System::Runtime::InteropServices;

namespace StillDesign
{
	namespace PhysX
	{
		generic< class T >
			where T : ref class, StillDesign::PhysX::IDisposable
		public ref class ReadOnlyElementCollection : ReadOnlyList<T>
		{
			public:
				ReadOnlyElementCollection();
			
			private:
				void ReadOnlyElementCollection_onAdd( System::Object^ sender, T item );
				void ReadOnlyElementCollection_onRemove( System::Object^ sender, T item );
				
				void ReadOnlyElement_onDisposing( System::Object^ sender, EventArgs^ e );
		};
		
		generic< class T, class R >
			where T : ref class, StillDesign::PhysX::IDisposable
			where R : ReadOnlyElementCollection<T>, gcnew()
		public ref class ElementCollection : List< T, R >
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
		
		//generic< class T >
		//	where T : ref class, IDisposable
		//public ref class ReadOnlyElementDictionary : ReadOnlyElementCollection< T >
		//{
		//	private:
		//		Dictionary< intptr_t, T >^ _dictionary;
		//	
		//	public:
		//		ReadOnlyElementDictionary();
		//		
		//	protected:
		//		virtual intptr_t GetPointerFromElement( T item )
		//		{
		//			throw gcnew NotImplementedException( "GetPointerFromElement function has not be overridden, report to developer" );
		//		}
		//	
		//	protected:
		//		virtual void OnAdd( Object^ sender, T item ) override;
		//		virtual void OnRemove( Object^ sender, T item ) override;
		//		
		//	internal:
		//		T GetElementByPointer( intptr_t pointer );
		//};
	};
};