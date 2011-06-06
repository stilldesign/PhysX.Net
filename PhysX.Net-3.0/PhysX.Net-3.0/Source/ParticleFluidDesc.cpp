#include "StdAfx.h"
#include "ParticleFluidDesc.h"

ParticleFluidDesc::ParticleFluidDesc([Optional] Nullable<TolerancesScale> scale)
	 : ParticleBaseDesc(ActorType::ParticleFluid, scale)
{
	SetToDefault(scale);
}

void ParticleFluidDesc::PopulateManaged(PxParticleFluidDesc& desc)
{
	ParticleBaseDesc::PopulateManaged(desc);

	this->RestParticleDistance = desc.restParticleDistance;
	this->Stiffness = desc.stiffness;
	this->Viscosity = desc.viscosity;
}
void ParticleFluidDesc::PopulateUnmanaged(PxParticleFluidDesc& desc)
{
	ParticleBaseDesc::PopulateUnmanaged(desc);

	desc.restParticleDistance = this->RestParticleDistance;
	desc.stiffness = this->Stiffness;
	desc.viscosity = this->Viscosity;
}

PxParticleFluidDesc ParticleFluidDesc::ToUnmanaged(ParticleFluidDesc^ desc)
{
	PxParticleFluidDesc d = PxParticleFluidDesc(PxTolerancesScale());
	
	desc->PopulateUnmanaged(d);

	return d;
}
ParticleFluidDesc^ ParticleFluidDesc::ToManaged(PxParticleFluidDesc desc)
{
	ParticleFluidDesc^ d = gcnew ParticleFluidDesc(Nullable<TolerancesScale>());

	d->PopulateManaged(desc);

	return d;
}

void ParticleFluidDesc::SetToDefault([Optional] Nullable<TolerancesScale> scale)
{
	ParticleBaseDesc::SetToDefault(scale);

	RestParticleDistance		= 0.02f;
	Stiffness					= 20.0f;
	Viscosity					= 6.0f;
}
bool ParticleFluidDesc::IsValid()
{
	auto d = ToUnmanaged(this);

	return d.isValid();
}