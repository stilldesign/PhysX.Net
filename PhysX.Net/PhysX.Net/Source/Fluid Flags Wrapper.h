#pragma once

#include "Fluid.h"

namespace StillDesign
{
	namespace PhysX
	{
		[System::ComponentModel::TypeConverter( System::ComponentModel::ExpandableObjectConverter::typeid )]
		public ref class FluidFlagsWrapper
		{
			private:
				Fluid^ _fluid;
				
			public:
				#define WRAPPER_PROPERTY( name ) \
					property bool name { \
						bool get() { return _fluid->GetFlag( FluidFlag::name ); } \
						void set(bool value) { _fluid->SetFlag( FluidFlag::name, value ); } \
					}
				
				WRAPPER_PROPERTY( Visualization )
				WRAPPER_PROPERTY( DisableGravity )
				WRAPPER_PROPERTY( CollisionTwoway )
				WRAPPER_PROPERTY( Enabled )
				WRAPPER_PROPERTY( Hardware )
				WRAPPER_PROPERTY( PriorityMode )
				WRAPPER_PROPERTY( ForceStrictCookingFormat )
				WRAPPER_PROPERTY( ProjectToPlane )
				
				#undef WRAPPER_PROPERTY
				
			internal:
				FluidFlagsWrapper( Fluid^ fluid )
				{
					if ( fluid == nullptr )
						throw gcnew ArgumentNullException( "fluid" );
					
					_fluid = fluid;
				}
		};
	}
}