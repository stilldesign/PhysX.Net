#include "StdAfx.h"

#include "Sphere Shape Description.h"
#include "Sphere Shape.h"
#include "Shape.h"
#include "Shape Description.h"
#include "Actor.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

SphereShapeDescription::SphereShapeDescription() : ShapeDescription( new NxSphereShapeDesc() )
{
	
}
SphereShapeDescription::SphereShapeDescription( float radius ) : ShapeDescription( new NxSphereShapeDesc() )
{
	this->Radius = radius;
}

float SphereShapeDescription::Radius::get()
{
	return this->UnmanagedPointer->radius;
}
void SphereShapeDescription::Radius::set( float value )
{
	this->UnmanagedPointer->radius = value;
}

NxSphereShapeDesc* SphereShapeDescription::UnmanagedPointer::get()
{
	return (NxSphereShapeDesc*)ShapeDescription::UnmanagedPointer;
}