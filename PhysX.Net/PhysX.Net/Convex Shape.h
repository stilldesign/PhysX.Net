#pragma once

#include <NxConvexShape.h> 

#include "Shape.h"
#include "Convex Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class Shape;
		ref class ConvexMesh;
		ref class Actor;
		
		public ref class ConvexShape : Shape
		{
			private:
				ConvexMesh^ _convexMesh;
			
			internal:
				ConvexShape( NxConvexShape* convexShape );
			
			public:	
				ConvexShapeDescription^ SaveToDescription();
				
				property StillDesign::PhysX::ConvexMesh^ ConvexMesh
				{
					StillDesign::PhysX::ConvexMesh^ get();
				}
			
			internal:
				property NxConvexShape* UnmanagedPointer
				{
					virtual NxConvexShape* get() new;
				}
		};
	};
};