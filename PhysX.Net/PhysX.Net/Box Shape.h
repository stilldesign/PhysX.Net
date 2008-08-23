#pragma once

#include "Shape.h"

UsingFrameworkNamespace

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
				
				Box GetWorldSpaceOBB();
				
				// <summary>Gets or Sets the dimensions of the box shape</summary>
				property Vector3 Dimensions
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Size of the box shape</summary>
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