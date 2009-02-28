#include "StdAfx.h"

#include "Point On Line Joint Description.h"

#include <NxPointOnLineJointDesc.h> 

using namespace StillDesign::PhysX;

PointOnLineJointDescription::PointOnLineJointDescription() : JointDescription( new NxPointOnLineJointDesc() )
{
	
}
PointOnLineJointDescription::PointOnLineJointDescription( NxPointOnLineJointDesc* desc ) : JointDescription( desc )
{
	
}

NxPointOnLineJointDesc* PointOnLineJointDescription::UnmanagedPointer::get()
{
	return (NxPointOnLineJointDesc*)JointDescription::UnmanagedPointer;
}