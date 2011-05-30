#include "StdAfx.h"
#include "RigidStatic.h"
#include <PxRigidStatic.h> 

RigidStatic::RigidStatic(PxRigidStatic* rigidStatic, PhysX::Physics^ owner)
	: RigidActor(rigidStatic, owner)
{
	
}

PxRigidStatic* RigidStatic::UnmanagedPointer::get()
{
	return (PxRigidStatic*)RigidActor::UnmanagedPointer;
}