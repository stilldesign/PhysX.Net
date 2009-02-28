#include "StdAfx.h"

#include "Point In Plane Joint Description.h"
#include "Point In Plane Joint.h"

#include <NxPointInPlaneJointDesc.h> 

using namespace StillDesign::PhysX;

PointInPlaneJointDescription::PointInPlaneJointDescription() : JointDescription( new NxPointInPlaneJointDesc() )
{
	
}
PointInPlaneJointDescription::PointInPlaneJointDescription( NxPointInPlaneJointDesc* desc ) : JointDescription( desc )
{
	
}

NxPointInPlaneJointDesc* PointInPlaneJointDescription::UnmanagedPointer::get()
{
	return (NxPointInPlaneJointDesc*)JointDescription::UnmanagedPointer;
}