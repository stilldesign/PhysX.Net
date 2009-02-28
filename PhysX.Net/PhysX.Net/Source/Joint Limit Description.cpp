#include "StdAfx.h"

#include "Joint Limit Description.h"

#include <NxJointLimitDesc.h> 

using namespace StillDesign::PhysX;

JointLimitDescription::JointLimitDescription( float value, float restitution, float hardness )
{
	_value = value;
	_restitution = restitution;
	_hardness = hardness;
}

JointLimitDescription::operator JointLimitDescription( NxJointLimitDesc jointLimitDescription )
{
	JointLimitDescription desc;
		desc.Value = jointLimitDescription.value;
		desc.Restitution = jointLimitDescription.restitution;
		desc.Hardness = jointLimitDescription.hardness;
	
	return desc;
}
JointLimitDescription::operator NxJointLimitDesc( JointLimitDescription jointLimitDescription )
{
	NxJointLimitDesc desc;
		desc.value = jointLimitDescription._value;
		desc.restitution = jointLimitDescription._restitution;
		desc.hardness = jointLimitDescription._hardness;
	
	return desc;
}

 float JointLimitDescription::Value::get()
{
	return _value;
}
void JointLimitDescription::Value::set( float value )
{
	_value = value;
}

float JointLimitDescription::Restitution::get()
{
	return _restitution;
}
void JointLimitDescription::Restitution::set( float value )
{
	_restitution = value;
}
float JointLimitDescription::Hardness::get()
{
	return _hardness;
}
void JointLimitDescription::Hardness::set( float value )
{
	_hardness = value;
}

//NxJointLimitDesc* JointLimitDescription::UnmanagedPointer::get()
//{
//	return _desc;
//}