#include "StdAfx.h"

#include "Sphere Force Field Shape.h"
#include "Force Field.h"

#include <NxSphereForceFieldShape.h> 

using namespace StillDesign::PhysX;

SphereForceFieldShape::SphereForceFieldShape( NxSphereForceFieldShape* sphereForceFieldShape ) : ForceFieldShape( sphereForceFieldShape )
{
	
}

float SphereForceFieldShape::Radius::get()
{
	return this->UnmanagedPointer->getRadius();
}
void SphereForceFieldShape::Radius::set( float value )
{
	this->UnmanagedPointer->setRadius( value );
}

NxSphereForceFieldShape* SphereForceFieldShape::UnmanagedPointer::get()
{
	return (NxSphereForceFieldShape*)ForceFieldShape::UnmanagedPointer;
}