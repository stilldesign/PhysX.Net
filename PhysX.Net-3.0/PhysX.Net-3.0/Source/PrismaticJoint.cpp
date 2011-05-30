#include "StdAfx.h"
#include "PrismaticJoint.h"
#include "JointLimitPair.h"
#include <PxPrismaticJoint.h> 

PrismaticJoint::PrismaticJoint(PxPrismaticJoint* joint, PhysX::Scene^ owner)
	: Joint(joint, JointType::Prismatic, owner)
{
	
}

JointLimitPair^ PrismaticJoint::Limit::get()
{
	return JointLimitPair::ToManaged(&this->UnmanagedPointer->getLimit());
}
void PrismaticJoint::Limit::set(JointLimitPair^ value)
{
	this->UnmanagedPointer->setLimit(JointLimitPair::ToUnmanaged(value));
}

PrismaticJointFlag PrismaticJoint::Flag::get()
{
	return ToManagedEnum(PrismaticJointFlag, this->UnmanagedPointer->getPrismaticJointFlags());
}
void PrismaticJoint::Flag::set(PrismaticJointFlag value)
{
	this->UnmanagedPointer->setPrismaticJointFlags(ToUnmanagedEnum(PxPrismaticJointFlag, value));
}

float PrismaticJoint::ProjectionLinearTolerance::get()
{
	return this->UnmanagedPointer->getProjectionLinearTolerance();
}
void PrismaticJoint::ProjectionLinearTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionLinearTolerance(value);
}

float PrismaticJoint::ProjectionAngularTolerance::get()
{
	return this->UnmanagedPointer->getProjectionAngularTolerance();
}
void PrismaticJoint::ProjectionAngularTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionAngularTolerance(value);
}

PxPrismaticJoint* PrismaticJoint::UnmanagedPointer::get()
{
	return (PxPrismaticJoint*)Joint::UnmanagedPointer;
}