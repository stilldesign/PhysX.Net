#pragma once

#include "Enums.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public ref class CompartmentDescription
		{
			private:
				NxCompartmentDesc* _desc;
			
			public:
				CompartmentDescription();
				~CompartmentDescription();
			protected:
				!CompartmentDescription();
			
			public:
				void SetToDefault();
				/// <summary>Returns true if the descriptor is valid</summary>
				bool IsValid();
				
				/// <summary></summary>
				property CompartmentType Type
				{
					CompartmentType get();
					void set( CompartmentType value );
				}
				/// <summary>Gets or Sets the device code  (incl. a PPU index from 0 to 31)</summary>
				property StillDesign::PhysX::DeviceCode DeviceCode
				{
					StillDesign::PhysX::DeviceCode get();
					void set( StillDesign::PhysX::DeviceCode value );
				}
				/// <summary></summary>
				property float GridHashCellSize
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property int GridHashTablePower
				{
					int get();
					void set( int value );
				}
				/// <summary></summary>
				property CompartmentFlag Flags
				{
					CompartmentFlag get();
					void set( CompartmentFlag value );
				}
				/// <summary></summary>
				property int ThreadMask
				{
					int get();
					void set( int value );
				}
				/// <summary></summary>
				property float Timescale
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxCompartmentDesc* UnmanagedPointer
				{
					NxCompartmentDesc* get();
				}
		};
	};
};