#include "StdAfx.h"

#include "Box Controller Description.h"

using namespace StillDesign::PhysX;

BoxControllerDescription::BoxControllerDescription( float sizeX, float sizeY, float sizeZ ) : ControllerDescription( new NxBoxControllerDesc() )
{
	this->Size = Vector3( sizeX, sizeY, sizeZ );
}
BoxControllerDescription::BoxControllerDescription( Vector3 size ) : ControllerDescription( new NxBoxControllerDesc() )
{
	this->Size = size;
}
BoxControllerDescription::BoxControllerDescription( Vector3 size, Vector3 position ) : ControllerDescription( new NxBoxControllerDesc() )
{
	this->Size = size;
	this->Position = position;
}
BoxControllerDescription::~BoxControllerDescription()
{
	this->!BoxControllerDescription();
}
BoxControllerDescription::!BoxControllerDescription()
{
	if( this->UnmanagedPointer != NULL )
	{
		delete this->UnmanagedPointer;
	}
}

Vector3 BoxControllerDescription::Extents::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->extents );
}
void BoxControllerDescription::Extents::set( Vector3 value )
{
	this->UnmanagedPointer->extents = Math::Vector3ToNxVec3( value );
}

Vector3 BoxControllerDescription::Size::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->extents * 2.0f );
}
void BoxControllerDescription::Size::set( Vector3 value )
{
	this->UnmanagedPointer->extents = Math::Vector3ToNxVec3( value * 0.5f );
}

NxBoxControllerDesc* BoxControllerDescription::UnmanagedPointer::get()
{
	return (NxBoxControllerDesc*)ControllerDescription::UnmanagedPointer;
}