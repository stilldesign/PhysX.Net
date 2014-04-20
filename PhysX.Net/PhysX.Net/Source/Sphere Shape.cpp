#include "StdAfx.h"

#include "Sphere Shape.h"
#include "Sphere Shape Description.h"
#include "Shape.h"
#include "Shape Description.h"
#include "Actor.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

SphereShape::SphereShape( NxSphereShape* sphereShape ) : Shape( sphereShape )
{
	
}

SphereShapeDescription^ SphereShape::SaveToDescription()
{
	SphereShapeDescription^ sphereShapeDesc = gcnew SphereShapeDescription();
		this->UnmanagedPointer->saveToDesc( *sphereShapeDesc->UnmanagedPointer );
		
	Shape::SaveToDescription( sphereShapeDesc );
	
	return sphereShapeDesc;
}

float SphereShape::Radius::get()
{
	return this->UnmanagedPointer->getRadius();
}
void SphereShape::Radius::set( float value )
{
	this->UnmanagedPointer->setRadius( value );
}

NxSphereShape* SphereShape::UnmanagedPointer::get()
{
	return (NxSphereShape*)Shape::UnmanagedPointer;
}