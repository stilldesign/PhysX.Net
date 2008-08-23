#pragma once

#include "Shape.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class SphereShape;
		ref class Scene;
		ref class SphereShapeDescription;
		
		public ref class SphereShape : Shape
		{
			internal:
				SphereShape( NxSphereShape* sphereShape );
			
			public:
				SphereShapeDescription^ SaveToDescription();
				
				/// <summary>Gets or Set the Radius of the Sphere</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxSphereShape* UnmanagedPointer
				{
					NxSphereShape* get() new;
				}
		};
	};
};