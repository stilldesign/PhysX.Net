#pragma once

#include "Force Field Shape.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class ForceFieldShapeGroup;
		
		public ref class BoxForceFieldShape : ForceFieldShape
		{
			internal:
				BoxForceFieldShape( NxBoxForceFieldShape* shape );
				
			public:
				property Vector3 Dimensions
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets the Size of the Box Shape</summary>
				property Vector3 Size
				{
					Vector3 get();
					void set( Vector3 value );
				}
			
			internal:
				property NxBoxForceFieldShape* UnmanagedPointer
				{
					virtual NxBoxForceFieldShape* get() new;
				}
		};
	};
};