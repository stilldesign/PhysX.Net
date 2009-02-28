#pragma once

#include "Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class ConvexShape;
		ref class ConvexMesh;
		ref class Scene;
		
		public ref class ConvexShapeDescription : ShapeDescription
		{
			private:
				ConvexMesh^ _convexMesh;
			
			public:
				ConvexShapeDescription();
				ConvexShapeDescription( ConvexMesh^ convexMesh );
				
			public:
				property StillDesign::PhysX::ConvexMesh^ ConvexMesh
				{
					StillDesign::PhysX::ConvexMesh^ get();
					void set( StillDesign::PhysX::ConvexMesh^ value );
				}
				property MeshShapeFlag MeshFlags
				{
					MeshShapeFlag get();
				}
			
			internal:
				property NxConvexShapeDesc* UnmanagedPointer
				{
					NxConvexShapeDesc* get() new;
				}
		};
	};
};