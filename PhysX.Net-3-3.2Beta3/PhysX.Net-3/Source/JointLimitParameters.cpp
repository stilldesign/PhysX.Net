#include "StdAfx.h"
#include "JointLimitParameters.h"

void JointLimitParameters::PopulateUnmanaged(PxJointLimitParameters* parameters)
{
	parameters->contactDistance = this->ContactDistance;
	parameters->damping = this->Damping;
	parameters->restitution = this->Restitution;
	parameters->spring = this->Spring;
}
void JointLimitParameters::PopulateManaged(PxJointLimitParameters* parameters)
{
	this->ContactDistance = parameters->contactDistance;
	this->Damping = parameters->damping;
	this->Restitution = parameters->restitution;
	this->Spring = parameters->spring;
}

JointLimitParameters^ JointLimitParameters::ToManaged(PxJointLimitParameters* parameters)
{
	if (parameters == NULL)
		throw gcnew ArgumentNullException("parameters");

	JointLimitParameters^ p = gcnew JointLimitParameters();
	
	p->PopulateManaged(parameters);

	return p;
}
PxJointLimitParameters* JointLimitParameters::ToUnmanaged(JointLimitParameters^ parameters)
{
	ThrowIfNull(parameters, "parameters");

	PxJointLimitParameters* p = new PxJointLimitParameters();
	
	parameters->PopulateUnmanaged(p);

	return p;
}