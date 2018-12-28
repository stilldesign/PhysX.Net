#include "StdAfx.h"
#include "SphericalJoint.h"
#include "JointLimitCone.h"

SphericalJoint::SphericalJoint(PxSphericalJoint* joint, PhysX::Physics^ owner)
	: Joint(joint, owner)
{

}

JointLimitCone^ SphericalJoint::GetLimitCone()
{
	PxJointLimitCone limitCone = this->UnmanagedPointer->getLimitCone();

	return JointLimitCone::ToManaged(limitCone);
}
void SphericalJoint::SetLimitCone(JointLimitCone^ limitCone)
{
	ThrowIfNull(limitCone, "limitCone");
	if (!limitCone->IsValid())
		throw gcnew ArgumentException("The limit cone is invalid", "limitCone");

	auto lc = JointLimitCone::ToUnmanaged(limitCone);

	this->UnmanagedPointer->setLimitCone(lc);
}

SphericalJointFlag SphericalJoint::Flags::get()
{
	return ToManagedEnum(SphericalJointFlag, this->UnmanagedPointer->getSphericalJointFlags());
}
void SphericalJoint::Flags::set(SphericalJointFlag value)
{
	auto f = ToUnmanagedEnum(PxSphericalJointFlag, value);
	this->UnmanagedPointer->setSphericalJointFlags(f);
}

float SphericalJoint::ProjectionLinearTolerance::get()
{
	return this->UnmanagedPointer->getProjectionLinearTolerance();
}
void SphericalJoint::ProjectionLinearTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionLinearTolerance(value);
}

float SphericalJoint::SwingYAngle::get()
{
	return this->UnmanagedPointer->getSwingYAngle();
}
float SphericalJoint::SwingZAngle::get()
{
	return this->UnmanagedPointer->getSwingZAngle();
}

PxSphericalJoint* SphericalJoint::UnmanagedPointer::get()
{
	return (PxSphericalJoint*)Joint::UnmanagedPointer;
}