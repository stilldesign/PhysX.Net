#include "StdAfx.h"

#include "Cylindrical Joint Description.h"
#include "Cylindrical Joint.h"
#include "Joint.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

CylindricalJointDescription::CylindricalJointDescription() : JointDescription( new NxCylindricalJointDesc() )
{
	
}
CylindricalJointDescription::CylindricalJointDescription( NxCylindricalJointDesc* desc ) : JointDescription( desc )
{
	
}

NxCylindricalJointDesc* CylindricalJointDescription::UnmanagedPointer::get()
{
	return (NxCylindricalJointDesc*)JointDescription::UnmanagedPointer;
}