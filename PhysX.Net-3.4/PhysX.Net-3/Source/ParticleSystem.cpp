#include "StdAfx.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(PxParticleSystem* particleSystem, PhysX::Physics^ owner)
	: ParticleBase(particleSystem, owner)
{
	
}

PxParticleSystem* ParticleSystem::UnmanagedPointer::get()
{
	return (PxParticleSystem*)ParticleBase::UnmanagedPointer;
}