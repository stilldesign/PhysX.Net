#pragma once

#include "Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class TriangleMesh;
		ref class TriangleMeshShape;
		ref class Scene;
		
		public ref class TriangleMeshShapeDescription : ShapeDescription
		{
			private:
				StillDesign::PhysX::TriangleMesh^ _triangleMesh;
			
			public:
				TriangleMeshShapeDescription();
			internal:
				TriangleMeshShapeDescription( NxTriangleMeshShapeDesc* triMeshShapeDesc );
				
			public:	
				property StillDesign::PhysX::TriangleMesh^ TriangleMesh
				{
					StillDesign::PhysX::TriangleMesh^ get();
					void set( StillDesign::PhysX::TriangleMesh^ value );
				}
				property MeshShapeFlag MeshFlags
				{
					MeshShapeFlag get();
					void set( MeshShapeFlag value );
				}
				property StillDesign::PhysX::MeshPagingMode MeshPagingMode
				{
					StillDesign::PhysX::MeshPagingMode get();
					void set( StillDesign::PhysX::MeshPagingMode value );
				}
			
			internal:
				property NxTriangleMeshShapeDesc* UnmanagedPointer
				{
					NxTriangleMeshShapeDesc* get() new;
				}
		};
	};
};