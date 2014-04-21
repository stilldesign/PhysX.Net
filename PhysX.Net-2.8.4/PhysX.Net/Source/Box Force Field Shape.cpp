#include "StdAfx.h"

#include "Box Force Field Shape.h"
#include "Force Field Shape Group.h"

#include <NxBoxForceFieldShape.h> 

using namespace StillDesign::PhysX;

BoxForceFieldShape::BoxForceFieldShape( NxBoxForceFieldShape* shape ) : ForceFieldShape( shape )
{
	
}

Vector3 BoxForceFieldShape::Dimensions::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getDimensions() );
}
void BoxForceFieldShape::Dimensions::set( Vector3 value )
{
	this->UnmanagedPointer->setDimensions( Math::Vector3ToNxVec3( value ) );
}

Vector3 BoxForceFieldShape::Size::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->getDimensions() ) * 2.0f;
}
void BoxForceFieldShape::Size::set( Vector3 value )
{
	this->UnmanagedPointer->setDimensions( Math::Vector3ToNxVec3( value ) / 2.0f );
}

NxBoxForceFieldShape* BoxForceFieldShape::UnmanagedPointer::get()
{
	return (NxBoxForceFieldShape*)ForceFieldShape::UnmanagedPointer;
}