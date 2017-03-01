#include "StdAfx.h"
#include "D6Joint.h"
#include "Scene.h"
#include "JointLimitCone.h"
#include "D6JointDrive.h"
#include "JointLinearLimit.h"
#include "JointAngularLimitPair.h"

D6Joint::D6Joint(PxD6Joint* joint, PhysX::Physics^ owner)
	: Joint(joint, owner)
{
	
}

D6Motion D6Joint::GetMotion(D6Axis axis)
{
	PxD6Axis::Enum a = (PxD6Axis::Enum)(PxU32)axis;

	return (D6Motion)(PxU32)this->UnmanagedPointer->getMotion(a);
}
void D6Joint::SetMotion(D6Axis axis, D6Motion motion)
{
	PxD6Axis::Enum a = (PxD6Axis::Enum)(PxU32)axis;
	PxD6Motion::Enum m = (PxD6Motion::Enum)(PxU32)motion;

	this->UnmanagedPointer->setMotion(a, m);
}

D6JointDrive^ D6Joint::GetDrive(D6Drive index)
{
	return D6JointDrive::ToManaged(this->UnmanagedPointer->getDrive(ToUnmanagedEnum(PxD6Drive, index)));
}
void D6Joint::SetDrive(D6Drive index, D6JointDrive^ drive)
{
	this->UnmanagedPointer->setDrive(ToUnmanagedEnum(PxD6Drive, index), D6JointDrive::ToUnmanaged(drive));
}

JointLinearLimit^ D6Joint::LinearLimit::get()
{
	return JointLinearLimit::ToManaged(this->UnmanagedPointer->getLinearLimit());
}
void D6Joint::LinearLimit::set(JointLinearLimit^ value)
{
	this->UnmanagedPointer->setLinearLimit(JointLinearLimit::ToUnmanaged(value));
}

JointAngularLimitPair^ D6Joint::TwistLimit::get()
{
	return JointAngularLimitPair::ToManaged(this->UnmanagedPointer->getTwistLimit());
}
void D6Joint::TwistLimit::set(JointAngularLimitPair^ value)
{
	this->UnmanagedPointer->setTwistLimit(JointAngularLimitPair::ToUnmanaged(value));
}

JointLimitCone^ D6Joint::SwingLimit::get()
{
	return JointLimitCone::ToManaged(this->UnmanagedPointer->getSwingLimit());
}
void D6Joint::SwingLimit::set(JointLimitCone^ value)
{
	this->UnmanagedPointer->setSwingLimit(JointLimitCone::ToUnmanaged(value));
}

Matrix D6Joint::DrivePosition::get()
{
	return MathUtil::PxTransformToMatrix(&this->UnmanagedPointer->getDrivePosition());
}
void D6Joint::DrivePosition::set(Matrix value)
{
	this->UnmanagedPointer->setDrivePosition(MathUtil::MatrixToPxTransform(value));
}

Vector3 D6Joint::DriveLinearVelocity::get()
{
	PxVec3 linear, angular;

	this->UnmanagedPointer->getDriveVelocity(linear, angular);

	return MathUtil::PxVec3ToVector3(linear);
}
void D6Joint::DriveLinearVelocity::set(Vector3 value)
{
	PxVec3 linear, angular;
	this->UnmanagedPointer->getDriveVelocity(linear, angular);

	this->UnmanagedPointer->setDriveVelocity(MathUtil::Vector3ToPxVec3(value), angular);
}

Vector3 D6Joint::DriveAngularVelocity::get()
{
	PxVec3 linear, angular;

	this->UnmanagedPointer->getDriveVelocity(linear, angular);

	return MathUtil::PxVec3ToVector3(angular);
}
void D6Joint::DriveAngularVelocity::set(Vector3 value)
{
	PxVec3 linear, angular;
	this->UnmanagedPointer->getDriveVelocity(linear, angular);

	this->UnmanagedPointer->setDriveVelocity(linear, MathUtil::Vector3ToPxVec3(value));
}

float D6Joint::ProjectionLinearTolerance::get()
{
	return this->UnmanagedPointer->getProjectionLinearTolerance();
}
void D6Joint::ProjectionLinearTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionLinearTolerance(value);
}

float D6Joint::ProjectionAngularTolerance::get()
{
	return this->UnmanagedPointer->getProjectionAngularTolerance();
}
void D6Joint::ProjectionAngularTolerance::set(float value)
{
	this->UnmanagedPointer->setProjectionAngularTolerance(value);
}

PxD6Joint* D6Joint::UnmanagedPointer::get()
{
	return (PxD6Joint*)Joint::UnmanagedPointer;
}