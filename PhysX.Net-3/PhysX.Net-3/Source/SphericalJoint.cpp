#include "StdAfx.h"
#include "SphericalJoint.h"
#include "JointLimitCone.h"
#include <PxSphericalJoint.h> 

SphericalJoint::SphericalJoint(PxSphericalJoint* joint, PhysX::Scene^ owner)
	: Joint(joint, JointType::Spherical, owner)
{

}

JointLimitCone^ SphericalJoint::LimitCone::get()
{
	return JointLimitCone::ToManaged(&this->UnmanagedPointer->getLimitCone());
}
void SphericalJoint::LimitCone::set(JointLimitCone^ value)
{
	this->UnmanagedPointer->setLimitCone(JointLimitCone::ToUnmanaged(value));
}

SphericalJointFlag SphericalJoint::Flags::get()
{
	return ToManagedEnum(SphericalJointFlag, this->UnmanagedPointer->getSphericalJointFlags());
}
void SphericalJoint::Flags::set(SphericalJointFlag value)
{
	this->UnmanagedPointer->setSphericalJointFlags(ToUnmanagedEnum(PxSphericalJointFlag, value));
}

float SphericalJoint::ProjectionLinearTolerance::get()
{
	return this->UnmanagedPointer->getProjectionLinearTolerance();
}
void SphericalJoint::ProjectionLinearTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionLinearTolerance(value);
}

PxSphericalJoint* SphericalJoint::UnmanagedPointer::get()
{
	return (PxSphericalJoint*)Joint::UnmanagedPointer;
}