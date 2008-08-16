#include "StdAfx.h"

#include "Cylindrical Joint.h"
#include "Cylindrical Joint Description.h"
#include "Joint.h"
#include "Scene.h"

using namespace StillDesign::PhysX;

CylindricalJoint::CylindricalJoint( NxCylindricalJoint* cylindricalJoint ) : Joint( cylindricalJoint )
{
	
}

void CylindricalJoint::LoadFromDescription( CylindricalJointDescription^ description )
{
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
CylindricalJointDescription^ CylindricalJoint::SaveToDescription()
{
	CylindricalJointDescription^ desc = gcnew CylindricalJointDescription();
		this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

NxCylindricalJoint* CylindricalJoint::UnmanagedPointer::get()
{
	return (NxCylindricalJoint*)Joint::UnmanagedPointer;
}