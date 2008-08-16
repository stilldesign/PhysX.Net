#include "StdAfx.h"

#include "Capsule Force Field Shape.h"
#include "Force Field Shape Group.h"

#include <NxCapsuleForceFieldShape.h> 

using namespace StillDesign::PhysX;

CapsuleForceFieldShape::CapsuleForceFieldShape( NxCapsuleForceFieldShape* shape ) : ForceFieldShape( shape )
{
	
}

float CapsuleForceFieldShape::Radius::get()
{
	return this->UnmanagedPointer->getRadius();
}
void CapsuleForceFieldShape::Radius::set( float value )
{
	this->UnmanagedPointer->setRadius( value );
}
float CapsuleForceFieldShape::Height::get()
{
	return this->UnmanagedPointer->getHeight();
}
void CapsuleForceFieldShape::Height::set( float value )
{
	this->UnmanagedPointer->setHeight( value );
}

NxCapsuleForceFieldShape* CapsuleForceFieldShape::UnmanagedPointer::get()
{
	return (NxCapsuleForceFieldShape*)ForceFieldShape::UnmanagedPointer;
}