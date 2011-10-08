#include "StdAfx.h"
#include "JointLimitCone.h"

JointLimitCone^ JointLimitCone::ToManaged(PxJointLimitCone* parameters)
{
	if (parameters == NULL)
		throw gcnew ArgumentNullException("parameters");

	JointLimitCone^ pair = gcnew JointLimitCone();

	pair->PopulateManaged(parameters);

	pair->YLimitAngle = parameters->yAngle;
	pair->ZLimitAngle = parameters->zAngle;

	return pair;
}
PxJointLimitCone JointLimitCone::ToUnmanaged(JointLimitCone^ parameters)
{
	ThrowIfNull(parameters, "parameters");

	PxJointLimitCone p(parameters->YLimitAngle, parameters->ZLimitAngle, parameters->LimitContactDistance);

	parameters->PopulateUnmanaged(&p);

	return p;
}