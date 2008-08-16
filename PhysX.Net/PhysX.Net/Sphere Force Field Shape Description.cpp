#include "StdAfx.h"

#include "Sphere Force Field Shape Description.h"
#include "Sphere Force Field Shape.h"
#include "Math.h"

#include <NxSphereForceFieldShapeDesc.h> 
#include <NxSphereForceFieldShape.h> 

using namespace StillDesign::PhysX;

SphereForceFieldShapeDescription::SphereForceFieldShapeDescription() : ForceFieldShapeDescription( new NxSphereForceFieldShapeDesc() )
{
	
}
SphereForceFieldShapeDescription::SphereForceFieldShapeDescription( NxSphereForceFieldShapeDesc* desc ) : ForceFieldShapeDescription( desc )
{
	
}

float SphereForceFieldShapeDescription::Radius::get()
{
	return this->UnmanagedPointer->radius;
}
void SphereForceFieldShapeDescription::Radius::set( float value )
{
	this->UnmanagedPointer->radius = value;
}

NxSphereForceFieldShapeDesc* SphereForceFieldShapeDescription::UnmanagedPointer::get()
{
	return (NxSphereForceFieldShapeDesc*)ForceFieldShapeDescription::UnmanagedPointer;
}