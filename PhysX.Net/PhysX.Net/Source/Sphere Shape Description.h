#pragma once

#include "Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class SphereShape;
		ref class Scene;
		
		public ref class SphereShapeDescription : ShapeDescription
		{
			public:
				SphereShapeDescription();
				SphereShapeDescription( float radius );
				
				/// <summary>Gets or Sets the Radius of the Car</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxSphereShapeDesc* UnmanagedPointer
				{
					NxSphereShapeDesc* get() new;
				}
		};
	};
};