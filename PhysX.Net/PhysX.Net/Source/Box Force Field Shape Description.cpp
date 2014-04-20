#include "StdAfx.h"

#include "Box Force Field Shape Description.h"
#include "Box Force Field Shape.h"
#include "Math.h"

#include <NxBoxForceFieldShapeDesc.h> 
#include <NxBoxForceFieldShape.h> 

using namespace StillDesign::PhysX;

BoxForceFieldShapeDescription::BoxForceFieldShapeDescription() : ForceFieldShapeDescription( new NxBoxForceFieldShapeDesc() )
{
	
}
BoxForceFieldShapeDescription::BoxForceFieldShapeDescription( NxBoxForceFieldShapeDesc* desc ) : ForceFieldShapeDescription( desc )
{
	
}

Vector3 BoxForceFieldShapeDescription::Size::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->dimensions ) * 2.0f;
}
void BoxForceFieldShapeDescription::Size::set( Vector3 value )
{
	this->UnmanagedPointer->dimensions = Math::Vector3ToNxVec3( value ) / 2.0f;
}

NxBoxForceFieldShapeDesc* BoxForceFieldShapeDescription::UnmanagedPointer::get()
{
	return (NxBoxForceFieldShapeDesc*)ForceFieldShapeDescription::UnmanagedPointer;
}