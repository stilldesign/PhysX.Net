#include "StdAfx.h"

#include "Prismatic Joint Description.h"
#include "Prismatic Joint.h"

#include <NxPrismaticJointDesc.h> 

using namespace StillDesign::PhysX;

PrismaticJointDescription::PrismaticJointDescription() : JointDescription( new NxPrismaticJointDesc() )
{
	
}
PrismaticJointDescription::PrismaticJointDescription( NxPrismaticJointDesc* desc ) : JointDescription( desc )
{
	
}

NxPrismaticJointDesc* PrismaticJointDescription::UnmanagedPointer::get()
{
	return (NxPrismaticJointDesc*)JointDescription::UnmanagedPointer;
}