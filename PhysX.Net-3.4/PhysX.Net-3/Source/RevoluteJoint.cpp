#include "StdAfx.h"
#include "RevoluteJoint.h"
#include "JointAngularLimitPair.h"

RevoluteJoint::RevoluteJoint(PxRevoluteJoint* joint, PhysX::Physics^ owner)
	: Joint(joint, owner)
{
	
}

float RevoluteJoint::Angle::get()
{
	return this->UnmanagedPointer->getAngle();
}

JointAngularLimitPair^ RevoluteJoint::Limit::get()
{
	return JointAngularLimitPair::ToManaged(this->UnmanagedPointer->getLimit());
}
void RevoluteJoint::Limit::set(JointAngularLimitPair^ value)
{
	this->UnmanagedPointer->setLimit(JointAngularLimitPair::ToUnmanaged(value));
}

float RevoluteJoint::DriveVelocity::get()
{
	return this->UnmanagedPointer->getDriveVelocity();
}
void RevoluteJoint::DriveVelocity::set(float value)
{
	this->UnmanagedPointer->setDriveVelocity(value);
}

float RevoluteJoint::DriveForceLimit::get()
{
	return this->UnmanagedPointer->getDriveForceLimit();
}
void RevoluteJoint::DriveForceLimit::set(float value)
{
	this->UnmanagedPointer->setDriveForceLimit(value);
}

float RevoluteJoint::DriveGearRatio::get()
{
	return this->UnmanagedPointer->getDriveGearRatio();
}
void RevoluteJoint::DriveGearRatio::set(float value)
{
	this->UnmanagedPointer->setDriveGearRatio(value);
}

RevoluteJointFlag RevoluteJoint::Flags::get()
{
	return ToManagedEnum(RevoluteJointFlag, this->UnmanagedPointer->getRevoluteJointFlags());
}
void RevoluteJoint::Flags::set(RevoluteJointFlag value)
{
	this->UnmanagedPointer->setRevoluteJointFlags(ToUnmanagedEnum(PxRevoluteJointFlag, value));
}

float RevoluteJoint::ProjectionLinearTolerance::get()
{
	return this->UnmanagedPointer->getProjectionLinearTolerance();
}
void RevoluteJoint::ProjectionLinearTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionLinearTolerance(value);
}

float RevoluteJoint::ProjectionAngularTolerance::get()
{
	return this->UnmanagedPointer->getProjectionAngularTolerance();
}
void RevoluteJoint::ProjectionAngularTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionAngularTolerance(value);
}

PxRevoluteJoint* RevoluteJoint::UnmanagedPointer::get()
{
	return (PxRevoluteJoint*)Joint::UnmanagedPointer;
}