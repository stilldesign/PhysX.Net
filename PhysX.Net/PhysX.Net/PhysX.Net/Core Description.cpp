#include "StdAfx.h"

#include "Core Description.h"

using namespace StillDesign::PhysX;

CoreDescription::CoreDescription()
{
	_desc = new NxPhysicsSDKDesc();
}
CoreDescription::CoreDescription( NxPhysicsSDKDesc* desc )
{
	Debug::Assert( desc != NULL );
	
	_desc = desc;
}
CoreDescription::~CoreDescription()
{
	 this->!CoreDescription();
}
CoreDescription::!CoreDescription()
{
	SAFE_DELETE( _desc );
}

bool CoreDescription::IsValid()
{
	return _desc->isValid();
}
void CoreDescription::SetToDefault()
{
	_desc->setToDefault();
}

int CoreDescription::HardwarePageSize::get()
{
	return _desc->hwPageSize;
}
void CoreDescription::HardwarePageSize::set( int value )
{
	_desc->hwPageSize = value;
}

int CoreDescription::HardwarePageMaximum::get()
{
	return _desc->hwPageMax;
}
void CoreDescription::HardwarePageMaximum::set( int value )
{
	_desc->hwPageMax = value;
}

int CoreDescription::HardwareConvexMaximum::get()
{
	return _desc->hwConvexMax;
}
void CoreDescription::HardwareConvexMaximum::set( int value )
{
	_desc->hwConvexMax = value;
}

unsigned int CoreDescription::CookerThreadMask::get()
{
	return _desc->cookerThreadMask;
}
void CoreDescription::CookerThreadMask::set( unsigned int value )
{
	_desc->cookerThreadMask = value;
}

CoreCreationFlag CoreDescription::Flags::get()
{
	return (CoreCreationFlag)_desc->flags;
}
void CoreDescription::Flags::set( CoreCreationFlag value )
{
	_desc->flags = (NxSDKCreationFlag)value;
}

NxPhysicsSDKDesc* CoreDescription::UnmanagedPointer::get()
{
	return _desc;
}