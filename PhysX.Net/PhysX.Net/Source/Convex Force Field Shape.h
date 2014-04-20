#pragma once

#include "Force Field Shape.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class ConvexForceFieldShapeDescription;
		ref class ConvexMesh;
		ref class ForceFieldShapeGroup;
		
		public ref class ConvexForceFieldShape : ForceFieldShape
		{
			private:
				StillDesign::PhysX::ConvexMesh^ _convexMesh;
			
			internal:
				ConvexForceFieldShape( NxConvexForceFieldShape* convexForceFieldShape, StillDesign::PhysX::ConvexMesh^ convexMesh );
				
			public:	
				/// <summary></summary>
				ConvexForceFieldShapeDescription^ SaveToDescription();
				
				/// <summary>Gets the convex mesh</summary>
				property StillDesign::PhysX::ConvexMesh^ ConvexMesh
				{
					StillDesign::PhysX::ConvexMesh^ get();
				}
			
			internal:
				property NxConvexForceFieldShape* UnmanagedPointer
				{
					NxConvexForceFieldShape* get() new;
				}
		};
	};
};