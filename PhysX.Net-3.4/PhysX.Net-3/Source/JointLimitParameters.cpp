#include "StdAfx.h"
#include "JointLimitParameters.h"

JointLimitParameters::JointLimitParameters(PxJointLimitParameters* parameters)
{
	if (parameters == NULL)
		throw gcnew ArgumentNullException("parameters");

	_parameters = parameters;
}
JointLimitParameters::~JointLimitParameters()
{
	this->!JointLimitParameters();
}
JointLimitParameters::!JointLimitParameters()
{
	// The unmanaged variable will be deleted by the derived class
	_parameters = NULL;
}

bool JointLimitParameters::Disposed::get()
{
	return (_parameters == NULL);
}

bool JointLimitParameters::IsValid()
{
	return _parameters->isValid();
}
bool JointLimitParameters::IsSoft()
{
	return _parameters->isSoft();
}

float JointLimitParameters::Restitution::get()
{
	return _parameters->restitution;
}
void JointLimitParameters::Restitution::set(float value)
{
	_parameters->restitution = value;
}

float JointLimitParameters::BounceThreshold::get()
{
	return _parameters->bounceThreshold;
}
void JointLimitParameters::BounceThreshold::set(float value)
{
	_parameters->bounceThreshold = value;
}

float JointLimitParameters::Stiffness::get()
{
	return _parameters->stiffness;
}
void JointLimitParameters::Stiffness::set(float value)
{
	_parameters->stiffness = value;
}

float JointLimitParameters::Damping::get()
{
	return _parameters->damping;
}
void JointLimitParameters::Damping::set(float value)
{
	_parameters->damping = value;
}

float JointLimitParameters::ContactDistance::get()
{
	return _parameters->contactDistance;
}
void JointLimitParameters::ContactDistance::set(float value)
{
	_parameters->contactDistance = value;
}

//

PxJointLimitParameters* JointLimitParameters::UnmanagedPointer::get()
{
	return _parameters;
}