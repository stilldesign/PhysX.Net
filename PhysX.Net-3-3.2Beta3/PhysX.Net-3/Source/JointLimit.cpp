#include "StdAfx.h"
#include "JointLimit.h"

JointLimit^ JointLimit::ToManaged(PxJointLimit* parameters)
{
	if (parameters == NULL)
		throw gcnew ArgumentNullException("parameters");

	JointLimit^ jointLimit = gcnew JointLimit();

	jointLimit->PopulateManaged(parameters);

	jointLimit->Value = parameters->value;

	return jointLimit;
}
PxJointLimit JointLimit::ToUnmanaged(JointLimit^ parameters)
{
	ThrowIfNull(parameters, "parameters");

	PxJointLimit jointLimit(parameters->Value, parameters->LimitContactDistance);

	parameters->PopulateUnmanaged(&jointLimit);
	
	return jointLimit;
}