#pragma once

#include "Fluid Description Base.h"

using namespace System;
UsingFrameworkNamespace

class NxFluidDesc;

namespace StillDesign
{
	namespace PhysX
	{
		ref class FluidEmitterDescription;
		ref class DescriptorValidity;
		ref class Scene;
		generic< class T > ref class ListBase;
		
		public ref class FluidDescription : FluidDescriptionBase
		{		
			private:
				ListBase< FluidEmitterDescription^ >^ _emitters;
			
			internal:
				FluidDescription( NxFluidDesc* desc );
			public:
				FluidDescription();
				~FluidDescription();
			protected:
				!FluidDescription();
			private:
				void CreateFluidDescription();
				
			public:
				/// <summary>(Re)sets the structure to the default</summary>
				void SetToDefault();
				/// <summary>Returns true if the current settings are valid</summary>
				bool IsValid();
				
				/// <summary>Gets a collection of emitter descriptors that describe emitters which emit fluid into this fluid actor</summary>
				property ListBase< FluidEmitterDescription^ >^ Emitters
				{
					ListBase< FluidEmitterDescription^ >^ get();
				}
			
			internal:
				property NxFluidDesc* UnmanagedPointer
				{
					NxFluidDesc* get();
				}
				
			private:
				void FluidEmitterDescriptionAdded( System::Object^ sender, FluidEmitterDescription^ e );
				void FluidEmitterDescriptionRemoved( System::Object^ sender, FluidEmitterDescription^ e );
		};
	};
};