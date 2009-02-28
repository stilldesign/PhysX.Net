#include "StdAfx.h"

#include "Pulley Joint.h"
#include "Pulley Joint Description.h"
#include "Joint.h"
#include "Motor Description.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

PulleyJoint::PulleyJoint( NxPulleyJoint* pulleyJoint ) : Joint( pulleyJoint )
{
	
}

void PulleyJoint::LoadFromDescription( PulleyJointDescription^ description )
{
	ThrowIfDescriptionIsNullOrInvalid( description, "description" );
	
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
PulleyJointDescription^ PulleyJoint::SaveToDescription()
{
	PulleyJointDescription^ desc = gcnew PulleyJointDescription();

	this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

PulleyJointFlag PulleyJoint::Flags::get()
{
	return (PulleyJointFlag)this->UnmanagedPointer->getFlags();
}
void PulleyJoint::Flags::set( PulleyJointFlag value )
{
	this->UnmanagedPointer->setFlags( (int)value );
}

MotorDescription PulleyJoint::Motor::get()
{
	NxMotorDesc motor;
	this->UnmanagedPointer->getMotor( motor );
	
	return (MotorDescription)motor;
}
void PulleyJoint::Motor::set( MotorDescription value )
{
	this->UnmanagedPointer->setMotor( (NxMotorDesc)value );
}
bool PulleyJoint::IsMotorEnabled::get()
{
	NxMotorDesc desc;
	
	return this->UnmanagedPointer->getMotor( desc );
}

NxPulleyJoint* PulleyJoint::UnmanagedPointer::get()
{
	return (NxPulleyJoint*)Joint::UnmanagedPointer;
}