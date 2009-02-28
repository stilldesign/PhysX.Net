#include "StdAfx.h"

#include "Triangle Mesh Shape Description.h"
#include "Enums.h"
#include "Shape Description.h"
#include "Triangle Mesh.h"
#include "Triangle Mesh Shape.h"
#include "Scene.h"
#include "Actor.h"
#include "Triangle Mesh Shape.h"
#include "Core.h"

using namespace StillDesign::PhysX;

TriangleMeshShapeDescription::TriangleMeshShapeDescription() : ShapeDescription( new NxTriangleMeshShapeDesc() )
{
	
}
TriangleMeshShapeDescription::TriangleMeshShapeDescription( NxTriangleMeshShapeDesc* triMeshShapeDesc ) : ShapeDescription( triMeshShapeDesc )
{
	if( triMeshShapeDesc->meshData != NULL )
		_triangleMesh = ObjectCache::GetObject<StillDesign::PhysX::TriangleMesh^>( (intptr_t)triMeshShapeDesc->meshData );
}

StillDesign::PhysX::TriangleMesh^ TriangleMeshShapeDescription::TriangleMesh::get()
{
	return _triangleMesh;
}
void TriangleMeshShapeDescription::TriangleMesh::set( StillDesign::PhysX::TriangleMesh^ value )
{
	_triangleMesh = value;
	
	if( value == nullptr )
		this->UnmanagedPointer->meshData = NULL;
	else
		this->UnmanagedPointer->meshData = value->UnmanagedPointer;
}

MeshShapeFlag TriangleMeshShapeDescription::MeshFlags::get()
{
	return (MeshShapeFlag)this->UnmanagedPointer->meshFlags;
}
void TriangleMeshShapeDescription::MeshFlags::set( MeshShapeFlag value )
{
	this->UnmanagedPointer->meshFlags = (int)value;
}

StillDesign::PhysX::MeshPagingMode TriangleMeshShapeDescription::MeshPagingMode::get()
{
	return (StillDesign::PhysX::MeshPagingMode)this->UnmanagedPointer->meshPagingMode;
}
void TriangleMeshShapeDescription::MeshPagingMode::set( StillDesign::PhysX::MeshPagingMode value )
{
	this->UnmanagedPointer->meshPagingMode = (NxMeshPagingMode)value;
}

NxTriangleMeshShapeDesc* TriangleMeshShapeDescription::UnmanagedPointer::get()
{
	return (NxTriangleMeshShapeDesc*)ShapeDescription::UnmanagedPointer;
}