#include "StdAfx.h"
#include "JointAngularLimitPair.h"

JointAngularLimitPair::JointAngularLimitPair(PxJointAngularLimitPair* unmanaged)
	: JointLimitParameters(unmanaged)
{

}
JointAngularLimitPair::JointAngularLimitPair(float lowerLimit, float upperLimit, [Optional] Nullable<float> contactDistance)
	: JointLimitParameters(new PxJointAngularLimitPair(lowerLimit, upperLimit, contactDistance.GetValueOrDefault(-1)))
{

}
JointAngularLimitPair::JointAngularLimitPair(float lowerLimit, float upperLimit, Spring spring)
	: JointLimitParameters(new PxJointAngularLimitPair(lowerLimit, upperLimit, Spring::ToUnmanaged(spring)))
{

}
JointAngularLimitPair::~JointAngularLimitPair()
{
	this->!JointAngularLimitPair();
}
JointAngularLimitPair::!JointAngularLimitPair()
{
	delete this->UnmanagedPointer;
}

JointAngularLimitPair^ JointAngularLimitPair::ToManaged(PxJointAngularLimitPair unmanaged)
{
	PxJointAngularLimitPair* copy = new PxJointAngularLimitPair(unmanaged);

	return gcnew JointAngularLimitPair(copy);
}
PxJointAngularLimitPair JointAngularLimitPair::ToUnmanaged(JointAngularLimitPair^ managed)
{
	ThrowIfNullOrDisposed(managed, "managed");

	return *managed->UnmanagedPointer;
}

//

float JointAngularLimitPair::Upper::get()
{
	return this->UnmanagedPointer->upper;
}
void JointAngularLimitPair::Upper::set(float value)
{
	this->UnmanagedPointer->upper = value;
}
float JointAngularLimitPair::Lower::get()
{
	return this->UnmanagedPointer->lower;
}
void JointAngularLimitPair::Lower::set(float value)
{
	this->UnmanagedPointer->lower = value;
}

PxJointAngularLimitPair* JointAngularLimitPair::UnmanagedPointer::get()
{
	return (PxJointAngularLimitPair*)JointLimitParameters::UnmanagedPointer;
}