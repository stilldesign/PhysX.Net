#include "StdAfx.h"
#include "FixedJoint.h"

FixedJoint::FixedJoint(PxFixedJoint* joint, PhysX::Physics^ owner)
	: Joint(joint, owner)
{
	
}

float FixedJoint::ProjectionLinearTolerance::get()
{
	return this->UnmanagedPointer->getProjectionLinearTolerance();
}
void FixedJoint::ProjectionLinearTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionLinearTolerance(value);
}

float FixedJoint::ProjectionAngularTolerance::get()
{
	return this->UnmanagedPointer->getProjectionAngularTolerance();
}
void FixedJoint::ProjectionAngularTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionAngularTolerance(value);
}

PxFixedJoint* FixedJoint::UnmanagedPointer::get()
{
	return (PxFixedJoint*)Joint::UnmanagedPointer;
}