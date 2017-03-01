#include "StdAfx.h"
#include "JointLinearLimit.h"

JointLinearLimit::JointLinearLimit(PxJointLinearLimit* unmanaged)
	: JointLimitParameters(unmanaged)
{

}
JointLinearLimit::JointLinearLimit(TolerancesScale scale, float extent, [Optional] Nullable<float> contactDistance)
	: JointLimitParameters(new PxJointLinearLimit(TolerancesScale::ToUnmanaged(scale), extent, contactDistance.GetValueOrDefault(-1)))
{

}
JointLinearLimit::JointLinearLimit(float extent, Spring spring)
	: JointLimitParameters(new PxJointLinearLimit(extent, Spring::ToUnmanaged(spring)))
{

}
JointLinearLimit::~JointLinearLimit()
{
	this->!JointLinearLimit();
}
JointLinearLimit::!JointLinearLimit()
{
	delete this->UnmanagedPointer;
}

JointLinearLimit^ JointLinearLimit::ToManaged(PxJointLinearLimit unmanaged)
{
	PxJointLinearLimit* copy = new PxJointLinearLimit(unmanaged);

	return gcnew JointLinearLimit(copy);
}
PxJointLinearLimit JointLinearLimit::ToUnmanaged(JointLinearLimit^ managed)
{
	ThrowIfNullOrDisposed(managed, "managed");

	return *managed->UnmanagedPointer;
}

//

float JointLinearLimit::Value::get()
{
	return this->UnmanagedPointer->value;
}
void JointLinearLimit::Value::set(float value)
{
	this->UnmanagedPointer->value = value;
}

PxJointLinearLimit* JointLinearLimit::UnmanagedPointer::get()
{
	return (PxJointLinearLimit*)JointLimitParameters::UnmanagedPointer;
}