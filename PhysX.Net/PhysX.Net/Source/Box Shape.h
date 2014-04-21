#pragma once

#include "Shape.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class BoxShape;
		value class Box;
		ref class BoxShapeDescription;
		
		public ref class BoxShape : Shape
		{
			internal:
				BoxShape( NxBoxShape* boxShape );
				
			public:
				BoxShapeDescription^ SaveToDescription();
				
				/// <summary>Gets the box represented as a world space OBB</summary>
				Box GetWorldSpaceOBB();
				
				/// <summary>Gets or Sets the dimensions of the box shape. The dimensions are the 'radii' of the box, meaning 1/2 extents in x dimension, 1/2 extents in y dimension, 1/2 extents in z dimension</summary>
				property Vector3 Dimensions
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the size of the box shape</summary>
				property Vector3 Size
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
			internal:
				property NxBoxShape* UnmanagedPointer
				{
					NxBoxShape* get() new;
				}
		};
	};
};