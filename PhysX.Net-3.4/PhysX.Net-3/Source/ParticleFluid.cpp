#include "StdAfx.h"
#include "ParticleFluid.h"
#include "ParticleFluidReadData.h"

ParticleFluid::ParticleFluid(PxParticleFluid* particleFluid, PhysX::Physics^ owner)
	: ParticleBase(particleFluid, owner)
{
	
}

ParticleFluidReadData^ ParticleFluid::LockParticleFluidReadData()
{
	return gcnew ParticleFluidReadData(this->UnmanagedPointer->lockParticleFluidReadData());
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
void ParticleFluid::RestParticleDistance::set(float value)
{
	this->UnmanagedPointer->setRestParticleDistance(value);
}

String^ ParticleFluid::ConcreteTypeName::get()
{
	return Util::ToManagedString(this->UnmanagedPointer->getConcreteTypeName());
}

PxParticleFluid* ParticleFluid::UnmanagedPointer::get()
{
	return (PxParticleFluid*)ParticleBase::UnmanagedPointer;
}