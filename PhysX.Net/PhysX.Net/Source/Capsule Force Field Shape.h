#pragma once

#include "Force Field Shape.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class ForceFieldShapeGroup;
		
		public ref class CapsuleForceFieldShape : ForceFieldShape
		{
			internal:
				CapsuleForceFieldShape( NxCapsuleForceFieldShape* shape );
				
			public:
				/// <summary>Gets or Sets the Radius of the Capsule Shape</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Height of the Capsule Shape. Height is the from the Centers of the Two Hemispheres</summary>
				/// <remarks>Total Height of a Capsule is h+r+r</remarks>
				property float Height
				{
					float get();
					void set( float value );
				}
				
			internal:
				property NxCapsuleForceFieldShape* UnmanagedPointer
				{
					virtual NxCapsuleForceFieldShape* get() new;
				}
		};
	};
};