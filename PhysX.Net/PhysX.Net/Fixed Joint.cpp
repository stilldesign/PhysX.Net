#include "StdAfx.h"

#include "Joint.h"
#include "Fixed Joint Description.h"
#include "Fixed Joint.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

FixedJoint::FixedJoint( NxFixedJoint* fixedJoint ) : Joint( fixedJoint )
{
	
}

void FixedJoint::LoadFromDescription( FixedJointDescription^ description )
{
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
FixedJointDescription^ FixedJoint::SaveToDescription()
{
	FixedJointDescription^ desc = gcnew FixedJointDescription();
		this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

NxFixedJoint* FixedJoint::UnmanagedPointer::get()
{
	return (NxFixedJoint*)Joint::UnmanagedPointer;
}