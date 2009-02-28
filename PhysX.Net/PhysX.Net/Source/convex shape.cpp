#include "StdAfx.h"

#include "Convex Shape.h"
#include "Shape.h"
#include "Actor.h"
#include "Scene.h"
#include "Convex Mesh.h"
#include "Convex Shape Description.h"
#include "Core.h"

using namespace StillDesign::PhysX;

ConvexShape::ConvexShape( NxConvexShape* convexShape ) : Shape( convexShape )
{
	_convexMesh = ObjectCache::GetObject<StillDesign::PhysX::ConvexMesh^>( (intptr_t)(&convexShape->getConvexMesh()) );
}

ConvexShapeDescription^ ConvexShape::SaveToDescription()
{
	ConvexShapeDescription^ convexShapeDesc = gcnew ConvexShapeDescription();
		this->UnmanagedPointer->saveToDesc( *convexShapeDesc->UnmanagedPointer );
		convexShapeDesc->ConvexMesh = _convexMesh;
		
	Shape::SaveToDescription( convexShapeDesc );
	
	return convexShapeDesc;
}

StillDesign::PhysX::ConvexMesh^ ConvexShape::ConvexMesh::get()
{
	return _convexMesh;
}
NxConvexShape* ConvexShape::UnmanagedPointer::get()
{
	return (NxConvexShape*)Shape::UnmanagedPointer;
}