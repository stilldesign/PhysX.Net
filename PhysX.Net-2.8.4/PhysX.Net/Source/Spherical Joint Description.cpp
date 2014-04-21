#include "StdAfx.h"

#include "Spherical Joint Description.h"
#include "Spherical Joint.h"
#include "Joint.h"
#include "Scene.h"
#include "Joint Limit Description.h"
#include "Joint Limit Pair Description.h"
#include "Spring Description.h"
#include "Actor.h"

#include <NxJoint.h> 
#include <NxSphericalJointDesc.h> 
#include <NxJointLimitPairDesc.h> 

using namespace StillDesign::PhysX;

SphericalJointDescription::SphericalJointDescription() : JointDescription( new NxSphericalJointDesc() )
{
	
}
SphericalJointDescription::SphericalJointDescription( NxSphericalJointDesc* desc ) : JointDescription( desc )
{
	
}

bool SphericalJointDescription::IsValid()
{
	return this->UnmanagedPointer->isValid();
}

Vector3 SphericalJointDescription::SwingAxis::get()
{
	return Math::NxVec3ToVector3( this->UnmanagedPointer->swingAxis );
}
void SphericalJointDescription::SwingAxis::set( Vector3 value )
{
	this->UnmanagedPointer->swingAxis = Math::Vector3ToNxVec3( value );
}

float SphericalJointDescription::ProjectionDistance::get()
{
	return  this->UnmanagedPointer->projectionDistance;
}
void SphericalJointDescription::ProjectionDistance::set( float value )
{
	this->UnmanagedPointer->projectionDistance = value;
}

JointLimitPairDescription SphericalJointDescription::TwistLimit::get()
{
	return (JointLimitPairDescription)this->UnmanagedPointer->twistLimit;
}
void SphericalJointDescription::TwistLimit::set( JointLimitPairDescription value )
{
	this->UnmanagedPointer->twistLimit = (NxJointLimitPairDesc)value;
}

JointLimitDescription SphericalJointDescription::SwingLimit::get()
{
	return (JointLimitDescription)this->UnmanagedPointer->swingLimit;
}
void SphericalJointDescription::SwingLimit::set( JointLimitDescription value )
{
	this->UnmanagedPointer->swingLimit = (NxJointLimitDesc)value;
}

SpringDescription SphericalJointDescription::TwistSpring::get()
{
	return (SpringDescription)this->UnmanagedPointer->twistSpring;
}
void SphericalJointDescription::TwistSpring::set( SpringDescription value )
{
	this->UnmanagedPointer->twistSpring = (NxSpringDesc)value;
}

SpringDescription SphericalJointDescription::SwingSpring::get()
{
	return (SpringDescription)this->UnmanagedPointer->swingSpring;
}
void SphericalJointDescription::SwingSpring::set( SpringDescription value )
{
	this->UnmanagedPointer->swingSpring = (NxSpringDesc)value;
}

SpringDescription SphericalJointDescription::JointSpring::get()
{
	return (SpringDescription)this->UnmanagedPointer->jointSpring;
}
void SphericalJointDescription::JointSpring::set( SpringDescription value )
{
	this->UnmanagedPointer->jointSpring = (NxSpringDesc)value;
}

SphericalJointFlag SphericalJointDescription::Flags::get()
{
	return (SphericalJointFlag)this->UnmanagedPointer->flags;
}
void SphericalJointDescription::Flags::set( SphericalJointFlag value )
{
	this->UnmanagedPointer->flags = (NxSphericalJointFlag)value;
}

JointProjectionMode SphericalJointDescription::ProjectionMode::get()
{
	return (JointProjectionMode)this->UnmanagedPointer->projectionMode;
}

void SphericalJointDescription::ProjectionMode::set( JointProjectionMode value )
{
	this->UnmanagedPointer->projectionMode = (NxJointProjectionMode)value;
}

NxSphericalJointDesc* SphericalJointDescription::UnmanagedPointer::get()
{
	return (NxSphericalJointDesc*)JointDescription::UnmanagedPointer;
}