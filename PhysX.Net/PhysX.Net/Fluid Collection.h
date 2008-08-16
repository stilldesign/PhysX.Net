//#pragma once
//
//using namespace System;
//using namespace stillDesign::Collections;
//
//namespace stillDesign
//{
//	namespace PhysX
//	{
//		ref class Fluid;
//		
//		public ref class FluidCollection : public BaseReadOnlyListNotifiable< Fluid^ >
//		{
//			private:
//				FluidCollection();
//			public:
//				~FluidCollection();
//				
//				static ReadOnlyListNotifiableConstructor< Fluid^ >^ FluidCollection::Create();
//				
//				void Fluid_onDisposing( System::Object^ sender, EventArgs^ e );
//				
//			public:
//				bool Contains( String^ name );
//				int IndexOf( String^ name );
//				
//				property Fluid^ default[ String^ ]
//				{
//					Fluid^ get( String^ name );
//				}
//			
//			private:
//				void FluidCollection_onAdd( System::Object^ sender, Fluid^ e );
//				void FluidCollection_onRemove( System::Object^ sender, Fluid^ e );
//		};
//	};
//};