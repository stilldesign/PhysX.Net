#include "StdAfx.h"

#include "Distance Joint.h"
#include "Distance Joint Description.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

DistanceJoint::DistanceJoint( NxDistanceJoint* distanceJoint ) : Joint( distanceJoint )
{
	
}

void DistanceJoint::LoadFromDescription( DistanceJointDescription^ description )
{
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
DistanceJointDescription^ DistanceJoint::SaveToDescription()
{
	DistanceJointDescription^ desc = gcnew DistanceJointDescription();
		this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

NxDistanceJoint* DistanceJoint::UnmanagedPointer::get()
{
	return (NxDistanceJoint*)Joint::UnmanagedPointer;
}