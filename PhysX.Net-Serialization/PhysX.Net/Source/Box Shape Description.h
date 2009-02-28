#pragma once

#include "Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		public ref class BoxShapeDescription : ShapeDescription
		{
			public:
				BoxShapeDescription();
				BoxShapeDescription( Vector3 size );
				BoxShapeDescription( float sizeX, float sizeY, float sizeZ );
				
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
				property NxBoxShapeDesc* UnmanagedPointer
				{
					NxBoxShapeDesc* get() new;
				}
		};
	};
};