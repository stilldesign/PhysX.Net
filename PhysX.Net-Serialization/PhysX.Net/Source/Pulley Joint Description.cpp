#include "StdAfx.h"

#include "Pulley Joint Description.h"
#include "Pulley Joint.h"
#include "Joint.h"
#include "Motor Description.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

PulleyJointDescription::PulleyJointDescription() : JointDescription( new NxPulleyJointDesc() )
{
	
}
PulleyJointDescription::PulleyJointDescription( NxPulleyJointDesc* desc ) : JointDescription( desc )
{
	
}

Vector3 PulleyJointDescription::SuspensionPointA::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->pulley[ 0 ] );
}
void PulleyJointDescription::SuspensionPointA::set( Vector3 value )
{
	this->UnmanagedPointer->pulley[ 0 ] = Math::Vector3ToNxVec3( value );
}
Vector3 PulleyJointDescription::SuspensionPointB::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->pulley[ 1 ] );
}
void PulleyJointDescription::SuspensionPointB::set( Vector3 value )
{
	this->UnmanagedPointer->pulley[ 1 ] = Math::Vector3ToNxVec3( value );
}
float PulleyJointDescription::Distance::get()
{
	return this->UnmanagedPointer->distance;
}
void PulleyJointDescription::Distance::set( float value )
{
	if( value < 0 )
		throw gcnew ArgumentException( "Distance value must be greater than or equal to 0" );
	
	this->UnmanagedPointer->distance = value;
}
float PulleyJointDescription::Stiffness::get()
{
	return this->UnmanagedPointer->stiffness;
}
void PulleyJointDescription::Stiffness::set( float value )
{
	if( value < 0 || value > 1 )
		throw gcnew ArgumentException( "Stiffness value must be between 0 and 1" );
	
	this->UnmanagedPointer->stiffness = value;
}
float PulleyJointDescription::Ratio::get()
{
	return this->UnmanagedPointer->ratio;
}
void PulleyJointDescription::Ratio::set( float value )
{
	this->UnmanagedPointer->ratio = value;
}
PulleyJointFlag PulleyJointDescription::Flags::get()
{
	return (PulleyJointFlag)this->UnmanagedPointer->flags;
}
void PulleyJointDescription::Flags::set( PulleyJointFlag value )
{
	this->UnmanagedPointer->flags = (int)value;
}

MotorDescription PulleyJointDescription::Motor::get()
{
	return (MotorDescription)this->UnmanagedPointer->motor;
}
void PulleyJointDescription::Motor::set( MotorDescription value )
{
	this->UnmanagedPointer->motor = (NxMotorDesc)value;
}

NxPulleyJointDesc* PulleyJointDescription::UnmanagedPointer::get()
{
	return (NxPulleyJointDesc*)JointDescription::UnmanagedPointer;
}