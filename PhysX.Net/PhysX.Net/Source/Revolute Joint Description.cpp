#include "StdAfx.h"

#include "Revolute Joint Description.h"
#include "Revolute Joint.h"
#include "Joint.h"
#include "Actor.h"
#include "Scene.h"
#include "Enums.h"
#include "Spring Description.h"
#include "Joint Limit Pair Description.h"
#include "Motor Description.h"

#include <NxRevoluteJointDesc.h> 

using namespace StillDesign::PhysX;

RevoluteJointDescription::RevoluteJointDescription() : JointDescription( new NxRevoluteJointDesc() )
{
	
}
RevoluteJointDescription::RevoluteJointDescription( NxRevoluteJointDesc* desc ) : JointDescription( desc )
{
	
}

bool RevoluteJointDescription::IsValid()
{
	return JointDescription::IsValid();
}

JointLimitPairDescription RevoluteJointDescription::Limit::get()
{
	return (JointLimitPairDescription)this->UnmanagedPointer->limit;
}
void RevoluteJointDescription::Limit::set( JointLimitPairDescription value )
{
	this->UnmanagedPointer->limit = (NxJointLimitPairDesc)value;
}
MotorDescription RevoluteJointDescription::Motor::get()
{
	return (MotorDescription)this->UnmanagedPointer->motor;
}
void RevoluteJointDescription::Motor::set( MotorDescription value )
{
	this->UnmanagedPointer->motor = (NxMotorDesc)value;
}
SpringDescription RevoluteJointDescription::Spring::get()
{
	return (SpringDescription)this->UnmanagedPointer->spring;
}
void RevoluteJointDescription::Spring::set( SpringDescription value )
{
	this->UnmanagedPointer->spring = (NxSpringDesc)value;
}
float RevoluteJointDescription::ProjectionDistance::get()
{
	return this->UnmanagedPointer->projectionDistance;
}
void RevoluteJointDescription::ProjectionDistance::set( float value )
{
	this->UnmanagedPointer->projectionDistance = value;
}

float RevoluteJointDescription::ProjectionAngle::get()
{
	return this->UnmanagedPointer->projectionAngle;
}
void RevoluteJointDescription::ProjectionAngle::set( float value )
{
	this->UnmanagedPointer->projectionAngle = value;
}
JointProjectionMode RevoluteJointDescription::ProjectionMode::get()
{
	return (JointProjectionMode)this->UnmanagedPointer->projectionMode;
}
void RevoluteJointDescription::ProjectionMode::set( JointProjectionMode value )
{
	this->UnmanagedPointer->projectionMode = (NxJointProjectionMode)value;
}

RevoluteJointFlag RevoluteJointDescription::Flags::get()
{
	return (RevoluteJointFlag)this->UnmanagedPointer->flags;
}
void RevoluteJointDescription::Flags::set( RevoluteJointFlag value )
{
	this->UnmanagedPointer->flags = (int)value;
}

NxRevoluteJointDesc* RevoluteJointDescription::UnmanagedPointer::get()
{
	return (NxRevoluteJointDesc*)JointDescription::UnmanagedPointer;
}