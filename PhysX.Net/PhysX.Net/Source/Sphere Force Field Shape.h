#pragma once

#include "Force Field Shape.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class ForceField;
		
		public ref class SphereForceFieldShape : ForceFieldShape
		{
			internal:
				SphereForceFieldShape( NxSphereForceFieldShape* sphereForceFieldShape );
			
			public:	
				/// <summary>Gets or Sets the Radius of the Sphere Shape</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxSphereForceFieldShape* UnmanagedPointer
				{
					virtual NxSphereForceFieldShape* get() new;
				}
		};
	};
};