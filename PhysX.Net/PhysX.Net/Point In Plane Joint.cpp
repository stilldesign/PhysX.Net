#include "StdAfx.h"

#include "Point In Plane Joint.h"
#include "Point In Plane Joint Description.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

PointInPlaneJoint::PointInPlaneJoint( NxPointInPlaneJoint* pointInPlaneJoint ) : Joint( pointInPlaneJoint )
{
	
}

void PointInPlaneJoint::LoadFromDescription( PointInPlaneJointDescription^ description )
{
	ThrowIfDescriptionIsNullOrInvalid( description, "description" );
	
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
PointInPlaneJointDescription^ PointInPlaneJoint::SaveToDescription()
{
	PointInPlaneJointDescription^ desc = gcnew PointInPlaneJointDescription();
	
	this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

NxPointInPlaneJoint* PointInPlaneJoint::UnmanagedPointer::get()
{
	return (NxPointInPlaneJoint*)Joint::UnmanagedPointer;
}