#include "StdAfx.h"
#include "ParticleCreationData.h"
#include <PxCoreUtilityTypes.h> 

PxParticleCreationData ParticleCreationData::ToUnmanaged(ParticleCreationData^ data)
{
	ThrowIfNull(data, "data");

	int n = data->NumberOfParticles;

	PxParticleCreationData d;
		d.numParticles = data->NumberOfParticles;
	
	const PxVec3* p = new PxVec3[n];
	Util::AsUnmanagedArray(data->PositionBuffer, (void*)p, data->NumberOfParticles);
	d.positionBuffer = PxStrideIterator<const PxVec3>(p);

	return d;
}