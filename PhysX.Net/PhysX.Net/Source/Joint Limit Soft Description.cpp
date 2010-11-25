#include "StdAfx.h"
#include "Joint Limit Soft Description.h"

#include <NxJointLimitSoftDesc.h> 

using namespace StillDesign::PhysX;

JointLimitSoftDescription::JointLimitSoftDescription( float value, float restitution, float spring, float damping )
{
	this->Value = value;
	this->Restitution = restitution;
	this->Spring = spring;
	this->Damping = damping;
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