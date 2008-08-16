#pragma once

#include "Force Field Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class BoxForceFieldShape;
		
		public ref class BoxForceFieldShapeDescription : ForceFieldShapeDescription
		{
			public:
				BoxForceFieldShapeDescription();
			internal:
				BoxForceFieldShapeDescription( NxBoxForceFieldShapeDesc* desc );
			
			public:
				/// <summary>Gets or Sets the Size of the Box Force Field Shape</summary>
				property Vector3 Size
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
			internal:
				property NxBoxForceFieldShapeDesc* UnmanagedPointer
				{
					NxBoxForceFieldShapeDesc* get() new;
				}
		};
	};
};