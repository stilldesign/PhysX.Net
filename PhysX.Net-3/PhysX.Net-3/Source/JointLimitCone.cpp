#include "StdAfx.h"
#include "JointLimitCone.h"

JointLimitCone::JointLimitCone()
{
	// Default values as per the documentation
	this->YLimitAngle = MathUtil::PiOver2;
	this->ZLimitAngle = MathUtil::PiOver2;
}
JointLimitCone::JointLimitCone(float yLimitAngle, float zLimitAngle, float limitContactDistance)
{
	// Default values as per the documentation
	this->YLimitAngle = MathUtil::PiOver2;
	this->ZLimitAngle = MathUtil::PiOver2;

	this->YLimitAngle = yLimitAngle;
	this->ZLimitAngle = zLimitAngle;
	this->LimitContactDistance = limitContactDistance;
}

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

	PxJointLimitCone p = PxJointLimitCone(parameters->YLimitAngle, parameters->ZLimitAngle, parameters->LimitContactDistance);

	parameters->PopulateUnmanaged(&p);

	return p;
}

bool JointLimitCone::IsValid()
{
	return ToUnmanaged(this).isValid();
}