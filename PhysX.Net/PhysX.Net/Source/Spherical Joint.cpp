#include "StdAfx.h"

#include "Spherical Joint.h"
#include "Spherical Joint Description.h"
#include "Joint.h"
#include "Scene.h"
#include "Actor.h"

using namespace StillDesign::PhysX;

SphericalJoint::SphericalJoint( NxSphericalJoint* sphericalJoint ) : Joint( sphericalJoint )
{
	
}

void SphericalJoint::LoadFromDescription( SphericalJointDescription^ description )
{
	ThrowIfDescriptionIsNullOrInvalid( description, "description" );
	
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
SphericalJointDescription^ SphericalJoint::SaveToDescription()
{
	SphericalJointDescription^ desc = gcnew SphericalJointDescription();
	
	this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
		
	return desc;
}

JointProjectionMode SphericalJoint::ProjectionMode::get()
{
	return (JointProjectionMode)this->UnmanagedPointer->getProjectionMode();
}
void SphericalJoint::ProjectionMode::set( JointProjectionMode value )
{
	this->UnmanagedPointer->setProjectionMode( (NxJointProjectionMode)value );
}

RevoluteJointFlag SphericalJoint::Flags::get()
{
	return (RevoluteJointFlag)this->UnmanagedPointer->getFlags();
}
void SphericalJoint::Flags::set( RevoluteJointFlag value )
{
	this->UnmanagedPointer->setFlags( (unsigned int)value );
}

NxSphericalJoint* SphericalJoint::UnmanagedPointer::get()
{
	return (NxSphericalJoint*)Joint::UnmanagedPointer;
}