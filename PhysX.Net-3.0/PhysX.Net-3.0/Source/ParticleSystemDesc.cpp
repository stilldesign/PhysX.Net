#include "StdAfx.h"
#include "ParticleSystemDesc.h"

ParticleSystemDesc::ParticleSystemDesc([Optional] Nullable<TolerancesScale> scale)
	: ParticleBaseDesc(ActorType::ParticleSystem, scale)
{
	
}

void ParticleSystemDesc::SetToDefault(TolerancesScale scale)
{
	
}
bool ParticleSystemDesc::IsValid()
{
	auto desc = ToUnmanaged(this);

	return desc.isValid();
}

PxParticleSystemDesc ParticleSystemDesc::ToUnmanaged(ParticleSystemDesc^ desc)
{
	PxParticleSystemDesc d = PxParticleSystemDesc(PxTolerancesScale());
	
	desc->PopulateUnmanaged(d);

	return d;
}