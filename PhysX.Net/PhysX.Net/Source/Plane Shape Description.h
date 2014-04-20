#pragma once

#include "Shape Description.h"

using namespace StillDesign::PhysX;

namespace StillDesign
{
	namespace PhysX
	{
		ref class PlaneShape;
		
		public ref class PlaneShapeDescription : ShapeDescription
		{
			public:
				PlaneShapeDescription();
				PlaneShapeDescription( Plane plane );
				PlaneShapeDescription( Vector3 normal, float distance );
				PlaneShapeDescription( float normalX, float normalY, float normalZ, float distance );
				
			public:
				/// <summary>Gets or Sets the Normal of the Plane</summary>
				property Vector3 Normal
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Distance Along the Normal from the Origin</summary>
				property float Distance
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxPlaneShapeDesc* UnmanagedPointer
				{
					NxPlaneShapeDesc* get() new;
				}
		};
	};
};