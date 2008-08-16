#include "StdAfx.h"

#include "Joint Drive Description.h"

#include <NxMotorDesc.h> 

using namespace StillDesign::PhysX;

JointDriveDescription::JointDriveDescription( float damping, D6JointDriveType driveType, float forceLimit, float spring )
{
	_damping = damping;
	_type = driveType;
	_forceLimit = forceLimit;
	_spring = spring;
}

JointDriveDescription JointDriveDescription::FromUnmanaged( NxJointDriveDesc jointDriveDescription )
{
	JointDriveDescription jointDriveDesc;
		jointDriveDesc.Damping = jointDriveDescription.damping;
		jointDriveDesc.DriveType = (D6JointDriveType)(NxU32)jointDriveDescription.driveType;
		jointDriveDesc.ForceLimit = jointDriveDescription.forceLimit;
		jointDriveDesc.Spring = jointDriveDescription.spring;
	
	return jointDriveDesc;
}
NxJointDriveDesc JointDriveDescription::ToUnmanaged( JointDriveDescription jointDriveDescription )
{
	NxJointDriveDesc jointDriveDesc;
		jointDriveDesc.damping = jointDriveDescription.Damping;
		jointDriveDesc.driveType = (NxU32)jointDriveDescription.DriveType;
		jointDriveDesc.forceLimit = jointDriveDescription.ForceLimit;
		jointDriveDesc.spring = jointDriveDescription.Spring;
	
	return jointDriveDesc;
}

float JointDriveDescription::Spring::get()
{
	return _spring;
}
void JointDriveDescription::Spring::set( float value )
{
	_spring = value;
}

float JointDriveDescription::Damping::get()
{
	return _damping;
}
void JointDriveDescription::Damping::set( float value )
{
	_damping = value;
}

D6JointDriveType JointDriveDescription::DriveType::get()
{
	return _type;
}
void JointDriveDescription::DriveType::set( D6JointDriveType value )
{
	_type = value;
}

float JointDriveDescription::ForceLimit::get()
{
	return _forceLimit;
}
void JointDriveDescription::ForceLimit::set( float value )
{
	_forceLimit = value;
}