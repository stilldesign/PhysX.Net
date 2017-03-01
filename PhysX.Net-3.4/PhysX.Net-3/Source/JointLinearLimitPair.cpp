#include "StdAfx.h"
#include "JointLinearLimitPair.h"

JointLinearLimitPair::JointLinearLimitPair(PxJointLinearLimitPair* unmanaged)
	: JointLimitParameters(unmanaged)
{

}
JointLinearLimitPair::JointLinearLimitPair(TolerancesScale scale, float lowerLimit, float upperLimit, [Optional] Nullable<float> contactDistance)
	: JointLimitParameters(new PxJointLinearLimitPair(TolerancesScale::ToUnmanaged(scale), lowerLimit, upperLimit, contactDistance.GetValueOrDefault(-1)))
{

}
JointLinearLimitPair::JointLinearLimitPair(float lowerLimit, float upperLimit, Spring spring)
	: JointLimitParameters(new PxJointLinearLimitPair(lowerLimit, upperLimit, Spring::ToUnmanaged(spring)))
{

}
JointLinearLimitPair::~JointLinearLimitPair()
{
	this->!JointLinearLimitPair();
}
JointLinearLimitPair::!JointLinearLimitPair()
{
	delete this->UnmanagedPointer;
}

JointLinearLimitPair^ JointLinearLimitPair::ToManaged(PxJointLinearLimitPair unmanaged)
{
	PxJointLinearLimitPair* copy = new PxJointLinearLimitPair(unmanaged);

	return gcnew JointLinearLimitPair(copy);
}
PxJointLinearLimitPair JointLinearLimitPair::ToUnmanaged(JointLinearLimitPair^ managed)
{
	ThrowIfNull(managed, "managed");

	return *managed->UnmanagedPointer;
}

//

float JointLinearLimitPair::Upper::get()
{
	return this->UnmanagedPointer->upper;
}
void JointLinearLimitPair::Upper::set(float value)
{
	this->UnmanagedPointer->upper = value;
}
float JointLinearLimitPair::Lower::get()
{
	return this->UnmanagedPointer->lower;
}
void JointLinearLimitPair::Lower::set(float value)
{
	this->UnmanagedPointer->lower = value;
}

PxJointLinearLimitPair* JointLinearLimitPair::UnmanagedPointer::get()
{
	return (PxJointLinearLimitPair*)JointLimitParameters::UnmanagedPointer;
}