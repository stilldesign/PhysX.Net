#include "StdAfx.h"
#include "ParticleFluidReadData.h"
#include <PxParticleFluidReadData.h> 

ParticleFluidReadData::ParticleFluidReadData(PxParticleFluidReadData* particleBase)
	: ParticleReadData(particleBase)
{
	
}

array<float>^ ParticleFluidReadData::GetDensityBuffer()
{
	return Util::AsManagedArray<float>((void*)this->UnmanagedPointer->densityBuffer.ptr(), this->NumberOfValidParticles);
}

PxParticleFluidReadData* ParticleFluidReadData::UnmanagedPointer::get()
{
	return (PxParticleFluidReadData*)ParticleReadData::UnmanagedPointer;	
}