#include "StdAfx.h"

#include "Fixed Joint Description.h"
#include "Fixed Joint.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

FixedJointDescription::FixedJointDescription() : JointDescription( new NxFixedJointDesc() )
{
	
}
FixedJointDescription::FixedJointDescription( NxFixedJointDesc* desc ) : JointDescription( desc )
{
	
}

NxFixedJointDesc* FixedJointDescription::UnmanagedPointer::get()
{
	return (NxFixedJointDesc*)JointDescription::UnmanagedPointer;
}