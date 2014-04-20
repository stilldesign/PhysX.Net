#include "StdAfx.h"

#include "Point On Line Joint.h"
#include "Point On Line Joint Description.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

PointOnLineJoint::PointOnLineJoint( NxPointOnLineJoint* pointOnLineJoint ) : Joint( pointOnLineJoint )
{
	
}

void PointOnLineJoint::LoadFromDescription( PointOnLineJointDescription^ description )
{
	ThrowIfDescriptionIsNullOrInvalid( description, "description" );
	
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
PointOnLineJointDescription^ PointOnLineJoint::SaveToDescription()
{
	PointOnLineJointDescription^ desc = gcnew PointOnLineJointDescription();

	this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

NxPointOnLineJoint* PointOnLineJoint::UnmanagedPointer::get()
{
	return (NxPointOnLineJoint*)Joint::UnmanagedPointer;
}