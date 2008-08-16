#include "StdAfx.h"

#include "Revolute Joint.h"
#include "Revolute Joint Description.h"
#include "Actor.h"
#include "Scene.h"
#include "Enums.h"
#include "Spring Description.h"
#include "Joint Limit Pair Description.h"
#include "Motor Description.h"
#include "Functions.h"

#include <NxRevoluteJoint.h> 

using namespace StillDesign::PhysX;

RevoluteJoint::RevoluteJoint( NxRevoluteJoint* revoluteJoint ) : Joint( revoluteJoint )
{
	
}

void RevoluteJoint::LoadFromDescription( RevoluteJointDescription^ description )
{
	if( description == nullptr )
		throw gcnew ArgumentNullException( "description" );
	
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
RevoluteJointDescription^ RevoluteJoint::SaveToDescription()
{
	RevoluteJointDescription^ desc = gcnew RevoluteJointDescription();
		this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

JointLimitPairDescription RevoluteJoint::Limits::get()
{
	NxJointLimitPairDesc limitPair;
	this->UnmanagedPointer->getLimits( limitPair );
	
	return (JointLimitPairDescription)limitPair;
}
void RevoluteJoint::Limits::set( JointLimitPairDescription value )
{
	this->UnmanagedPointer->setLimits( (NxJointLimitPairDesc)value );
}
MotorDescription RevoluteJoint::Motor::get()
{
	NxMotorDesc motor;
	this->UnmanagedPointer->getMotor( motor );
	
	return (MotorDescription)motor;
}
void RevoluteJoint::Motor::set( MotorDescription value )
{
	this->UnmanagedPointer->setMotor( (NxMotorDesc)value );
}
SpringDescription RevoluteJoint::Spring::get()
{
	NxSpringDesc spring;
	this->UnmanagedPointer->getSpring( spring );
	
	return (SpringDescription)spring;
}
void RevoluteJoint::Spring::set( SpringDescription value )
{
	this->UnmanagedPointer->setSpring( (NxSpringDesc)value );
}
float RevoluteJoint::Angle::get()
{
	return this->UnmanagedPointer->getAngle();
}
float RevoluteJoint::Velocity::get()
{
	return this->UnmanagedPointer->getVelocity();
}
RevoluteJointFlag RevoluteJoint::Flags::get()
{
	return (RevoluteJointFlag)this->UnmanagedPointer->getFlags();
}
void RevoluteJoint::Flags::set( RevoluteJointFlag value )
{
	this->UnmanagedPointer->setFlags( (NxRevoluteJointFlag)value );
}

JointProjectionMode RevoluteJoint::ProjectionMode::get()
{
	return (JointProjectionMode)this->UnmanagedPointer->getProjectionMode();
}
void RevoluteJoint::ProjectionMode::set( JointProjectionMode value )
{
	return this->UnmanagedPointer->setProjectionMode( (NxJointProjectionMode)value );
}

NxRevoluteJoint* RevoluteJoint::UnmanagedPointer::get()
{
	return (NxRevoluteJoint*)Joint::UnmanagedPointer;
}