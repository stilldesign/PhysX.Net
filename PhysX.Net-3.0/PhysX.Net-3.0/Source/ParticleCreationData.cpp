#include "StdAfx.h"
#include "ParticleCreationData.h"

PxParticleCreationData ParticleCreationData::ToUnmanaged(ParticleCreationData^ data)
{
	PxParticleCreationData d;
		d.numParticles = data->NumberOfParticles;
	
	return d;
}