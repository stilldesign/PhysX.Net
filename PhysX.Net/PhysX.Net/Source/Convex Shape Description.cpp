#include "StdAfx.h"

#include "Convex Shape Description.h"
#include "Convex Shape.h"
#include "Convex Mesh.h"
#include "Shape Description.h"
#include "Scene.h"
#include "Material.h"
#include "Actor.h"

using namespace StillDesign::PhysX;

ConvexShapeDescription::ConvexShapeDescription() : ShapeDescription( new NxConvexShapeDesc() )
{
	
}
ConvexShapeDescription::ConvexShapeDescription( StillDesign::PhysX::ConvexMesh^ convexMesh ) : ShapeDescription( new NxConvexShapeDesc() )
{
	ThrowIfDisposed( convexMesh, "convexMesh" );

	this->ConvexMesh = convexMesh;
}

StillDesign::PhysX::ConvexMesh^ ConvexShapeDescription::ConvexMesh::get()
{
	return _convexMesh;
}
void ConvexShapeDescription::ConvexMesh::set( StillDesign::PhysX::ConvexMesh^ value )
{
	_convexMesh = value;
	
	if( value == nullptr )
		this->UnmanagedPointer->meshData = NULL;
	else
		this->UnmanagedPointer->meshData = value->UnmanagedPointer;
}

MeshShapeFlag ConvexShapeDescription::MeshFlags::get()
{
	return (MeshShapeFlag)this->UnmanagedPointer->meshFlags;
}

NxConvexShapeDesc* ConvexShapeDescription::UnmanagedPointer::get()
{
	return (NxConvexShapeDesc*)ShapeDescription::UnmanagedPointer;
}