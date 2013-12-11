#include "StdAfx.h"
#include "ParticleCreationData.h"
//#include <PxCoreUtilityTypes.h> 

PxParticleCreationData ParticleCreationData::ToUnmanaged(ParticleCreationData^ data)
{
	ThrowIfNull(data, "data");

	int n = data->NumberOfParticles;

	PxParticleCreationData d;
		d.numParticles = data->NumberOfParticles;
	
	if (data->IndexBuffer != nullptr)
	{
		PxU32* i = new PxU32[n];
		Util::AsUnmanagedArray(data->IndexBuffer, i, n);
		d.indexBuffer = PxStrideIterator<const PxU32>(i);
	}

	if (data->PositionBuffer != nullptr)
	{
		PxVec3* p = new PxVec3[n];
		Util::AsUnmanagedArray(data->PositionBuffer, p, n);
		d.positionBuffer = PxStrideIterator<const PxVec3>(p);
	}

	if (data->VelocityBuffer != nullptr)
	{
		PxVec3* v = new PxVec3[n];
		Util::AsUnmanagedArray(data->VelocityBuffer, v, n);
		d.velocityBuffer = PxStrideIterator<const PxVec3>(v);
	}

	if (data->RestOffsetBuffer != nullptr)
	{
		float* r = new float[n];
		Util::AsUnmanagedArray(data->RestOffsetBuffer, r, n);
		d.restOffsetBuffer = PxStrideIterator<const float>(r);
	}

	if (data->FlagBuffer != nullptr)
	{
		PxU32* f = new PxU32[n];
		Util::AsUnmanagedArray(data->FlagBuffer, f, n);
		d.flagBuffer = PxStrideIterator<const PxU32>(f);
	}
	
	return d;
}