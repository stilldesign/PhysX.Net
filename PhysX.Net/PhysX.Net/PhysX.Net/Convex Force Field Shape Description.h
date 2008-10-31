#pragma once 

#include "Force Field Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class ConvexMesh;
		ref class Core;
		
		public ref class ConvexForceFieldShapeDescription : ForceFieldShapeDescription
		{
			private:
				StillDesign::PhysX::ConvexMesh^ _convexMesh;
			
			public:
				ConvexForceFieldShapeDescription();
			internal:
				ConvexForceFieldShapeDescription( NxConvexForceFieldShapeDesc* desc );
			
			public:
				/// <summary></summary>
				void SetToDefault();
				/// <summary></summary>
				bool IsValid();
				
				/// <summary></summary>
				property StillDesign::PhysX::ConvexMesh^ ConvexMesh
				{
					StillDesign::PhysX::ConvexMesh^ get();
					void set( StillDesign::PhysX::ConvexMesh^ value );
				}
			
			internal:
				property NxConvexForceFieldShapeDesc* UnmanagedPointer
				{
					virtual NxConvexForceFieldShapeDesc* get() new;
				}
		};
	};
};