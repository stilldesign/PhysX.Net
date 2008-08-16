#pragma once

#include "Enums.h"
#include "Base Shape.h"

class NxTriangleMeshShape;

namespace StillDesign
{
	namespace PhysX
	{
		ref class OverlappingResult;
		value class Bounds3;
		ref class TriangleMeshShapeDescription;
		ref class TriangleMesh;
		
		public ref class TriangleMeshShape : Shape
		{
			private:
				StillDesign::PhysX::TriangleMesh^ _triangleMesh;
			
			internal:
				TriangleMeshShape( NxTriangleMeshShape* triangleMeshShape );
				
			public:	
				TriangleMeshShapeDescription^ SaveToDescription();
				
				void UnmapPageInstance( int pageIndex );
				bool IsPageInstanceMapped( int pageIndex );
				array<int>^ IsOverlappingAABBTriangles( Bounds3 bounds, QueryFlag queryFlags );
				
				property StillDesign::PhysX::TriangleMesh^ TriangleMesh
				{
					StillDesign::PhysX::TriangleMesh^ get();
				}
			
			internal:
				property NxTriangleMeshShape* UnmanagedPointer
				{
					NxTriangleMeshShape* get() new;
				}
		};
	};
};