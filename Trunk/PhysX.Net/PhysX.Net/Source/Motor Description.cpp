#include "StdAfx.h"

#include "Motor Description.h"

#include <NxMotorDesc.h> 

using namespace StillDesign::PhysX;

MotorDescription::MotorDescription( float velocityTarget, float maxForce, bool freeSpinEnabled )
{
	_velocityTarget = velocityTarget;
	_maximumForce = maxForce;
	_freeSpin = freeSpinEnabled;
}

MotorDescription::operator MotorDescription( NxMotorDesc motorDescription )
{
	return MotorDescription( motorDescription.velTarget, motorDescription.maxForce, motorDescription.freeSpin );
}
MotorDescription::operator NxMotorDesc( MotorDescription motorDescription )
{
	return NxMotorDesc( motorDescription.VelocityTarget, motorDescription.MaximumForce, motorDescription.FreeSpinEnabled );
}

bool MotorDescription::IsValid()
{
	return true;
}

float MotorDescription::VelocityTarget::get()
{
	return _velocityTarget;
}
void MotorDescription::VelocityTarget::set( float value )
{
	_velocityTarget = value;
}

float MotorDescription::MaximumForce::get()
{
	return _maximumForce;
}
void MotorDescription::MaximumForce::set( float value )
{
	_maximumForce = value;
}

bool MotorDescription::FreeSpinEnabled::get()
{
	return _freeSpin;
}
void MotorDescription::FreeSpinEnabled::set( bool value )
{
	_freeSpin = value;
}