#pragma once

#include "Base Shape.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class PlaneShape;
		ref class Scene;
		ref class PlaneShapeDescription;
		
		public ref class PlaneShape : Shape
		{
			internal:
				PlaneShape( NxPlaneShape* planeShape );
				
			public:	
				PlaneShapeDescription^ SaveToDescription();
				
				property float Distance
				{
					float get();
					void set( float value );
				}
				property Vector3 Normal
				{
					Vector3 get();
					void set( Vector3 value );
				}
			
			internal:
				property NxPlaneShape* UnmanagedPointer
				{
					NxPlaneShape* get() new;
				}
		};
	};
};