#include "StdAfx.h"

#include "Triangle Mesh Shape.h"
#include "Shape Description.h"
#include "Base Shape.h"
#include "Actor.h"
#include "Scene.h"
#include "Bounds.h"
#include "Triangle Mesh Shape Description.h"
#include "Triangle Mesh.h"
#include "Core.h"

#include <NxTriangleMeshShape.h> 

using namespace StillDesign::PhysX;

TriangleMeshShape::TriangleMeshShape( NxTriangleMeshShape* triangleMeshShape ) : Shape( triangleMeshShape )
{
	_triangleMesh = ObjectCache::GetObject<StillDesign::PhysX::TriangleMesh^>( (intptr_t)(&triangleMeshShape->getTriangleMesh()) );
}

TriangleMeshShapeDescription^ TriangleMeshShape::SaveToDescription()
{
	NxTriangleMeshShapeDesc* desc = new NxTriangleMeshShapeDesc();
		this->UnmanagedPointer->saveToDesc( *desc );
	
	TriangleMeshShapeDescription^ triangleMeshShapeDesc = gcnew TriangleMeshShapeDescription( desc );
		
	Shape::SaveToDescription( triangleMeshShapeDesc );
	
	return triangleMeshShapeDesc;
}

void TriangleMeshShape::UnmapPageInstance( int pageIndex )
{
	this->UnmanagedPointer->unmapPageInstance( pageIndex );
}
bool TriangleMeshShape::IsPageInstanceMapped( int pageIndex )
{
	return this->UnmanagedPointer->isPageInstanceMapped( pageIndex );
}
array<int>^ TriangleMeshShape::IsOverlappingAABBTriangles( Bounds3 bounds, QueryFlag queryFlags )
{
	const NxU32* i;
	NxU32 c;
	bool overlap = this->UnmanagedPointer->overlapAABBTriangles( (NxBounds3)bounds, (NxU32)queryFlags, c, i );
	
	if( overlap == false )
	{
		return nullptr;
	}else{
		array<int>^ indices = gcnew array<int>( c * 3 );
		for( unsigned int x = 0; x < c; x++ )
		{
			indices[ x ] = i[ x ];
		}
		
		delete i;
		
		return indices;
	}
}

StillDesign::PhysX::TriangleMesh^ TriangleMeshShape::TriangleMesh::get()
{
	return _triangleMesh;
}

NxTriangleMeshShape* TriangleMeshShape::UnmanagedPointer::get()
{
	return (NxTriangleMeshShape*)Shape::UnmanagedPointer;
}