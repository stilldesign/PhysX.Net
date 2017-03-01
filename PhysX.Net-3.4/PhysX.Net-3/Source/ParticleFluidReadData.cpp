#include "StdAfx.h"
#include "ParticleFluidReadData.h"

ParticleFluidReadData::ParticleFluidReadData(PxParticleFluidReadData* particleBase)
	: ParticleReadData(particleBase)
{
}

array<float>^ ParticleFluidReadData::GetDensityBuffer()
{
	const int n = this->NumberOfValidParticles;

	if (n <= 0)
		return nullptr;

	array<float>^ ret = gcnew array<float>(n);

	for (int i = 0; i < n; i++)
		ret[i] = this->UnmanagedPointer->densityBuffer[i];

	return ret;
}

PxParticleFluidReadData* ParticleFluidReadData::UnmanagedPointer::get()
{
	return (PxParticleFluidReadData*)ParticleReadData::UnmanagedPointer;	
}