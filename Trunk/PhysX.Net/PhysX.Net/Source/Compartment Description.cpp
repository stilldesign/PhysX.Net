#include "StdAfx.h"

#include "Compartment Description.h"

#include <NxCompartmentDesc.h> 

using namespace StillDesign::PhysX;

CompartmentDescription::CompartmentDescription()
{
	_desc = new NxCompartmentDesc();
}
CompartmentDescription::~CompartmentDescription()
{
	this->!CompartmentDescription();
}
CompartmentDescription::!CompartmentDescription()
{
	SAFE_DELETE( _desc );
}

void CompartmentDescription::SetToDefault()
{
	_desc->setToDefault();
}
bool CompartmentDescription::IsValid()
{
	return _desc->isValid();
}

CompartmentType CompartmentDescription::Type::get()
{
	return (CompartmentType)_desc->type;
}
void CompartmentDescription::Type::set( CompartmentType value )
{
	_desc->type = (NxCompartmentType)value;
}

StillDesign::PhysX::DeviceCode CompartmentDescription::DeviceCode::get()
{
	return (StillDesign::PhysX::DeviceCode)_desc->deviceCode;
}
void CompartmentDescription::DeviceCode::set( StillDesign::PhysX::DeviceCode value )
{
	_desc->deviceCode = (NxU32)value;
}

float CompartmentDescription::GridHashCellSize::get()
{
	return _desc->gridHashCellSize;
}
void CompartmentDescription::GridHashCellSize::set( float value )
{
	_desc->gridHashCellSize = value;
}

int CompartmentDescription::GridHashTablePower::get()
{
	return _desc->gridHashTablePower;
}
void CompartmentDescription::GridHashTablePower::set( int value )
{
	_desc->gridHashTablePower = value;
}

CompartmentFlag CompartmentDescription::Flags::get()
{
	return (CompartmentFlag)_desc->flags;
}
void CompartmentDescription::Flags::set( CompartmentFlag value )
{
	_desc->flags = (NxCompartmentFlag)value;
}

int CompartmentDescription::ThreadMask::get()
{
	return _desc->threadMask;
}
void CompartmentDescription::ThreadMask::set( int value )
{
	_desc->threadMask = value;
}

float CompartmentDescription::Timescale::get()
{
	return _desc->timeScale;
}
void CompartmentDescription::Timescale::set( float value )
{
	_desc->timeScale = value;
}

NxCompartmentDesc* CompartmentDescription::UnmanagedPointer::get()
{
	return _desc;
}