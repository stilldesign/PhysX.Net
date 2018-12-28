#include "StdAfx.h"
#include "RigidStatic.h"

RigidStatic::RigidStatic(PxRigidStatic* rigidStatic, PhysX::IDisposable^ owner)
	: RigidActor(rigidStatic, owner)
{
	
}

PxRigidStatic* RigidStatic::UnmanagedPointer::get()
{
	return (PxRigidStatic*)RigidActor::UnmanagedPointer;
}