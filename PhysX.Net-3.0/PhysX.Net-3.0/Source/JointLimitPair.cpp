#include "StdAfx.h"
#include "JointLimitPair.h"

JointLimitPair^ JointLimitPair::ToManaged(PxJointLimitPair* parameters)
{
	if (parameters == NULL)
		throw gcnew ArgumentNullException("parameters");

	JointLimitPair^ pair = gcnew JointLimitPair();

	pair->PopulateManaged(parameters);

	pair->LowerLimit = parameters->lower;
	pair->UpperLimit = parameters->upper;

	return pair;
}
PxJointLimitPair JointLimitPair::ToUnmanaged(JointLimitPair^ parameters)
{
	ThrowIfNull(parameters, "parameters");

	PxJointLimitPair p(parameters->LowerLimit, parameters->UpperLimit, parameters->LimitContactDistance);

	parameters->PopulateUnmanaged(&p);
	
	return p;
}