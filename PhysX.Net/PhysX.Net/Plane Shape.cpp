#include "StdAfx.h"

#include "Plane Shape.h"
#include "Shape Description.h"
#include "Base Shape.h"
#include "Actor.h"
#include "Scene.h"
#include "Plane Shape Description.h"

using namespace StillDesign::PhysX;

PlaneShape::PlaneShape( NxPlaneShape* planeShape ) : Shape( planeShape )
{
	
}

PlaneShapeDescription^ PlaneShape::SaveToDescription()
{
	PlaneShapeDescription^ planeShapeDesc = gcnew PlaneShapeDescription();
		this->UnmanagedPointer->saveToDesc( *planeShapeDesc->UnmanagedPointer );
		
	Shape::SaveToDescription( planeShapeDesc );
	
	return planeShapeDesc;
}

float PlaneShape::Distance::get()
{
	return this->UnmanagedPointer->getPlane().d;
}
void PlaneShape::Distance::set( float value )
{
	this->UnmanagedPointer->setPlane( this->UnmanagedPointer->getPlane().normal, value );
}

Vector3 PlaneShape::Normal::get()
{
	const NxPlane plane = this->UnmanagedPointer->getPlane();
	
	return Vector3( plane.normal.x, plane.normal.y, plane.normal.z );
}
void PlaneShape::Normal::set( Vector3 value )
{
	this->UnmanagedPointer->setPlane( Math::Vector3ToNxVec3( value ), this->UnmanagedPointer->getPlane().d );
}

NxPlaneShape* PlaneShape::UnmanagedPointer::get()
{
	return (NxPlaneShape*)Shape::UnmanagedPointer;
}