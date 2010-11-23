#include "StdAfx.h"

#include "Convex Force Field Shape.h"
#include "Convex Force Field Shape Description.h"
#include "Scene.h"
#include "Force Field Shape Group.h"
#include "Convex Mesh.h"

using namespace StillDesign::PhysX;

ConvexForceFieldShape::ConvexForceFieldShape( NxConvexForceFieldShape* convexForceFieldShape, StillDesign::PhysX::ConvexMesh^ convexMesh ) : ForceFieldShape( convexForceFieldShape )
{
	Debug::Assert( convexForceFieldShape != NULL );
	ThrowIfNullOrDisposed( convexMesh, "convexMesh" );
	
	_convexMesh = convexMesh;
}

ConvexForceFieldShapeDescription^ ConvexForceFieldShape::SaveToDescription()
{
	NxConvexForceFieldShapeDesc* desc = new NxConvexForceFieldShapeDesc();
	this->UnmanagedPointer->saveToDesc( *desc );
	
	// Convex mesh does not need to be passed in
	return gcnew ConvexForceFieldShapeDescription( desc );
}

StillDesign::PhysX::ConvexMesh^ ConvexForceFieldShape::ConvexMesh::get()
{
	return _convexMesh;
}
NxConvexForceFieldShape* ConvexForceFieldShape::UnmanagedPointer::get()
{
	return (NxConvexForceFieldShape*)ForceFieldShape::UnmanagedPointer;
}