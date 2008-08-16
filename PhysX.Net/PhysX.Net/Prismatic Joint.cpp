#include "StdAfx.h"

#include "Prismatic Joint.h"
#include "Prismatic Joint Description.h"
#include "Scene.h"

#include <NxPrismaticJoint.h> 

using namespace StillDesign::PhysX;

PrismaticJoint::PrismaticJoint( NxPrismaticJoint* prismaticJoint ) : Joint( prismaticJoint )
{
	
}

void PrismaticJoint::LoadFromDescription( PrismaticJointDescription^ description )
{
	this->UnmanagedPointer->loadFromDesc( *description->UnmanagedPointer );
	
	Joint::LoadFromDescription( description );
}
PrismaticJointDescription^ PrismaticJoint::SaveToDescription()
{
	PrismaticJointDescription^ desc = gcnew PrismaticJointDescription();
		this->UnmanagedPointer->saveToDesc( *desc->UnmanagedPointer );
	
	Joint::SaveToDescription( desc );
	
	return desc;
}

NxPrismaticJoint* PrismaticJoint::UnmanagedPointer::get()
{
	return (NxPrismaticJoint*)Joint::UnmanagedPointer;
}