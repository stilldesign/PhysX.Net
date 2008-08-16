#pragma once

#include "Force Field Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class SphereForceFieldShape;
		
		public ref class SphereForceFieldShapeDescription : ForceFieldShapeDescription
		{
			public:
				SphereForceFieldShapeDescription();
			internal:
				SphereForceFieldShapeDescription( NxSphereForceFieldShapeDesc* desc );
				
			public:
				/// <summary>Gets or Sets the Radius of the Sphere Force Field Shape</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				
			internal:
				property NxSphereForceFieldShapeDesc* UnmanagedPointer
				{
					NxSphereForceFieldShapeDesc* get() new;
				}
		};
	};
};