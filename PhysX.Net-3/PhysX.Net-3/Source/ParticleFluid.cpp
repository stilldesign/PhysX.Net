#include "StdAfx.h"
#include "ParticleFluid.h"
#include "ParticleFluidReadData.h"
#include "ParticleFluidDesc.h"

ParticleFluid::ParticleFluid(PxParticleFluid* particleFluid, PhysX::Physics^ owner)
	: ParticleBase(particleFluid, owner)
{
	
}

ParticleFluidReadData^ ParticleFluid::LockParticleFluidReadData()
{
	return gcnew ParticleFluidReadData(this->UnmanagedPointer->lockParticleFluidReadData());
}

ParticleFluidDesc^ ParticleFluid::SaveToDesc()
{
	PxParticleFluidDesc desc = PxParticleFluidDesc(PxTolerancesScale());
	this->UnmanagedPointer->saveToDesc(desc);

	return ParticleFluidDesc::ToManaged(desc);
}

float ParticleFluid::Stiffness::get()
{
	return this->UnmanagedPointer->getStiffness();
}
void ParticleFluid::Stiffness::set(float value)
{
	this->UnmanagedPointer->setStiffness(value);
}

float ParticleFluid::Viscosity::get()
{
	return this->UnmanagedPointer->getViscosity();
}
void ParticleFluid::Viscosity::set(float value)
{
	this->UnmanagedPointer->setViscosity(value);
}

float ParticleFluid::RestParticleDistance::get()
{
	return this->UnmanagedPointer->getRestParticleDistance();
}

PxParticleFluid* ParticleFluid::UnmanagedPointer::get()
{
	return (PxParticleFluid*)ParticleBase::UnmanagedPointer;
}