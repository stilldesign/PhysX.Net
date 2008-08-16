#include "StdAfx.h"

#include "Box Shape Description.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

BoxShapeDescription::BoxShapeDescription() : ShapeDescription( new NxBoxShapeDesc() )
{
	
}
BoxShapeDescription::BoxShapeDescription( Vector3 size ) : ShapeDescription( new NxBoxShapeDesc() )
{
	this->Size = size;
}
BoxShapeDescription::BoxShapeDescription( float sizeX, float sizeY, float sizeZ ) : ShapeDescription( new NxBoxShapeDesc() )
{
	this->Size = Vector3( sizeX, sizeY, sizeZ );
}

Vector3 BoxShapeDescription::Dimensions::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->dimensions );
}
void BoxShapeDescription::Dimensions::set( Vector3 value )
{
	this->UnmanagedPointer->dimensions = Math::Vector3ToNxVec3( value );
}
Vector3 BoxShapeDescription::Size::get()
{
	NxVec3 dim = this->UnmanagedPointer->dimensions;
	
	return Math::NxVec3ToVector3( dim ) * 2.0f;
}
void BoxShapeDescription::Size::set( Vector3 value )
{
	this->UnmanagedPointer->dimensions = Math::Vector3ToNxVec3( value * 0.5f );
}

NxBoxShapeDesc* BoxShapeDescription::UnmanagedPointer::get()
{
	return (NxBoxShapeDesc*)ShapeDescription::UnmanagedPointer;
}