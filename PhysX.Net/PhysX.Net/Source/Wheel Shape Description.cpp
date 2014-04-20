#include "StdAfx.h"

#include "Wheel Shape Description.h"
#include "Scene.h"
#include "Actor.h"
#include "Spring Description.h"
#include "User Wheel Contact Modify.h"

using namespace StillDesign::PhysX;

WheelShapeDescription::WheelShapeDescription() : ShapeDescription( new NxWheelShapeDesc() )
{
	
}

bool WheelShapeDescription::IsValid()
{
	return this->UnmanagedPointer->isValid();
}
void WheelShapeDescription::SetToDefault()
{
	this->UnmanagedPointer->setToDefault();
}

UserWheelContactModify^ WheelShapeDescription::WheelContactModify::get()
{
	return _wheelContactModify;
}
void WheelShapeDescription::WheelContactModify::set( UserWheelContactModify^ value )
{
	_wheelContactModify = value;
}

float WheelShapeDescription::Radius::get()
{
	return this->UnmanagedPointer->radius;
}
void WheelShapeDescription::Radius::set( float value )
{
	this->UnmanagedPointer->radius = value;
}

float WheelShapeDescription::SuspensionTravel::get()
{
	return this->UnmanagedPointer->suspensionTravel;
}
void WheelShapeDescription::SuspensionTravel::set( float value )
{
	this->UnmanagedPointer->suspensionTravel = value;
}

SpringDescription WheelShapeDescription::Suspension::get()
{
	return (SpringDescription)this->UnmanagedPointer->suspension;
}
void WheelShapeDescription::Suspension::set( SpringDescription value )
{
	this->UnmanagedPointer->suspension = (NxSpringDesc)value;
}

TireFunctionDescription WheelShapeDescription::LongitudalTireForceFunction::get()
{
	return (TireFunctionDescription)this->UnmanagedPointer->longitudalTireForceFunction;
}
void WheelShapeDescription::LongitudalTireForceFunction::set( TireFunctionDescription value )
{
	this->UnmanagedPointer->longitudalTireForceFunction = (NxTireFunctionDesc)value;
}

TireFunctionDescription WheelShapeDescription::LateralTireForceFunction::get()
{
	return (TireFunctionDescription)this->UnmanagedPointer->lateralTireForceFunction;
}
void WheelShapeDescription::LateralTireForceFunction::set( TireFunctionDescription value )
{
	this->UnmanagedPointer->lateralTireForceFunction = (NxTireFunctionDesc)value;
}

float WheelShapeDescription::InverseWheelMass::get()
{
	return this->UnmanagedPointer->inverseWheelMass;
}
void WheelShapeDescription::InverseWheelMass::set( float value )
{
	this->UnmanagedPointer->inverseWheelMass = value;
}

WheelShapeFlag WheelShapeDescription::Flags::get()
{
	return (WheelShapeFlag)this->UnmanagedPointer->wheelFlags;
}
void WheelShapeDescription::Flags::set( WheelShapeFlag value )
{
	this->UnmanagedPointer->wheelFlags = (NxWheelShapeFlags)value;
}

float WheelShapeDescription::MotorTorque::get()
{
	return this->UnmanagedPointer->motorTorque;
}
void WheelShapeDescription::MotorTorque::set( float value )
{
	this->UnmanagedPointer->motorTorque = value;
}

float WheelShapeDescription::BrakeTorque::get()
{
	return this->UnmanagedPointer->brakeTorque;
}
void WheelShapeDescription::BrakeTorque::set( float value )
{
	this->UnmanagedPointer->brakeTorque = value;
}

float WheelShapeDescription::SteerAngle::get()
{
	return this->UnmanagedPointer->steerAngle;
}
void WheelShapeDescription::SteerAngle::set( float value )
{
	this->UnmanagedPointer->steerAngle = value;
}

NxWheelShapeDesc* WheelShapeDescription::UnmanagedPointer::get()
{
	return (NxWheelShapeDesc*)ShapeDescription::UnmanagedPointer;
}