#include "StdAfx.h"

#include "Joint Limit Soft Description.h"

#include <NxJointLimitSoftDesc.h> 

using namespace StillDesign::PhysX;

JointLimitSoftDescription::JointLimitSoftDescription( float value, float restitution, float spring, float damping )
{
	_value = value;
	_restitution = restitution;
	_spring = spring;
	_damping = damping;
}

JointLimitSoftDescription JointLimitSoftDescription::FromUnmanaged( NxJointLimitSoftDesc jointLimitSoftDesc )
{
	JointLimitSoftDescription desc;
		desc.Damping = jointLimitSoftDesc.damping;
		desc.Spring = jointLimitSoftDesc.spring;
		desc.Restitution = jointLimitSoftDesc.restitution;
		desc.Value = jointLimitSoftDesc.value;
	
	return desc;
}
NxJointLimitSoftDesc JointLimitSoftDescription::ToUnmanaged( JointLimitSoftDescription jointLimitSoftDescription )
{
	NxJointLimitSoftDesc desc;
		desc.damping = jointLimitSoftDescription.Damping;
		desc.spring = jointLimitSoftDescription.Spring;
		desc.restitution = jointLimitSoftDescription.Restitution;
		desc.value = jointLimitSoftDescription.Value;
	
	return desc;
}

float JointLimitSoftDescription::Value::get()
{
	return _value;
}
void JointLimitSoftDescription::Value::set( float value )
{
	_value = value;
}

float JointLimitSoftDescription::Restitution::get()
{
	return _restitution;
}
void JointLimitSoftDescription::Restitution::set( float value )
{
	_restitution = value;
}

float JointLimitSoftDescription::Spring::get()
{
	return _spring;
}
void JointLimitSoftDescription::Spring::set( float value )
{
	_spring = value;
}

float JointLimitSoftDescription::Damping::get()
{
	return _damping;
}
void JointLimitSoftDescription::Damping::set( float value )
{
	_damping = value;
}