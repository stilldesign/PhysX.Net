#include "StdAfx.h"

#include "Capsule Force Field Shape Description.h"
#include "Capsule Force Field Shape.h"
#include "Math.h"

#include <NxCapsuleForceFieldShapeDesc.h> 
#include <NxCapsuleForceFieldShape.h> 

using namespace StillDesign::PhysX;

CapsuleForceFieldShapeDescription::CapsuleForceFieldShapeDescription() : ForceFieldShapeDescription( new NxCapsuleForceFieldShapeDesc() )
{
	
}
CapsuleForceFieldShapeDescription::CapsuleForceFieldShapeDescription( NxCapsuleForceFieldShapeDesc* desc ) : ForceFieldShapeDescription( desc )
{
	
}

float CapsuleForceFieldShapeDescription::Radius::get()
{
	return this->UnmanagedPointer->radius;
}
void CapsuleForceFieldShapeDescription::Radius::set( float value )
{
	this->UnmanagedPointer->radius = value;
}
float CapsuleForceFieldShapeDescription::Height::get()
{
	return this->UnmanagedPointer->height;
}
void CapsuleForceFieldShapeDescription::Height::set( float value )
{
	this->UnmanagedPointer->height = value;
}

NxCapsuleForceFieldShapeDesc* CapsuleForceFieldShapeDescription::UnmanagedPointer::get()
{
	return (NxCapsuleForceFieldShapeDesc*)ForceFieldShapeDescription::UnmanagedPointer;
}