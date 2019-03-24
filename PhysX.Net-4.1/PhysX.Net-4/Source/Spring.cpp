#include "StdAfx.h"
#include "Spring.h"

PxSpring Spring::ToUnmanaged(Spring managed)
{
	return PxSpring(managed.Stiffness, managed.Damping);
}
Spring Spring::ToManaged(PxSpring unmanaged)
{
	return Spring(unmanaged.stiffness, unmanaged.damping);
}

Spring::Spring(float stiffness, float damping)
{
	this->Stiffness = stiffness;
	this->Damping = damping;
}