#include "StdAfx.h"
#include "JointLimitCone.h"

JointLimitCone::JointLimitCone(PxJointLimitCone* unmanaged)
	: JointLimitParameters(unmanaged)
{

}
JointLimitCone::JointLimitCone()
	: JointLimitParameters(new PxJointLimitCone(0, 0))
{

}
JointLimitCone::JointLimitCone(float yLimitAngle, float zLimitAngle, [Optional] Nullable<float> contactDistance)
	: JointLimitParameters(new PxJointLimitCone(yLimitAngle, zLimitAngle, contactDistance.GetValueOrDefault(-1)))
{
	
}
JointLimitCone::JointLimitCone(float yLimitAngle, float zLimitAngle, Spring spring)
	: JointLimitParameters(new PxJointLimitCone(yLimitAngle, zLimitAngle, Spring::ToUnmanaged(spring)))
{

}
JointLimitCone::~JointLimitCone()
{
	this->!JointLimitCone();
}
JointLimitCone::!JointLimitCone()
{
	delete this->UnmanagedPointer;
}

JointLimitCone^ JointLimitCone::ToManaged(PxJointLimitCone unmanaged)
{
	PxJointLimitCone* copy = new PxJointLimitCone(unmanaged);

	return gcnew JointLimitCone(copy);
}
PxJointLimitCone JointLimitCone::ToUnmanaged(JointLimitCone^ managed)
{
	ThrowIfNullOrDisposed(managed, "managed");

	return *managed->UnmanagedPointer;
}

float JointLimitCone::YLimitAngle::get()
{
	return this->UnmanagedPointer->yAngle;
}
void JointLimitCone::YLimitAngle::set(float value)
{
	this->UnmanagedPointer->yAngle = value;
}

float JointLimitCone::ZLimitAngle::get()
{
	return this->UnmanagedPointer->zAngle;
}
void JointLimitCone::ZLimitAngle::set(float value)
{
	this->UnmanagedPointer->zAngle = value;
}

PxJointLimitCone* JointLimitCone::UnmanagedPointer::get()
{
	return (PxJointLimitCone*)JointLimitParameters::UnmanagedPointer;
}