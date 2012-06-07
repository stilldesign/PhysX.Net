#include "StdAfx.h"
#include "ParticleBaseDesc.h"
#include <PxParticleBaseDesc.h> 

ParticleBaseDesc::ParticleBaseDesc(ActorType type, [Optional] Nullable<TolerancesScale> scale)
	: ActorDesc(type)
{
	
}

void ParticleBaseDesc::PopulateManaged(PxParticleBaseDesc& desc)
{
	ActorDesc::PopulateManaged(desc);

	this->MaximumParticles = desc.maxParticles;
	this->MaximumMotionDistance = desc.maxMotionDistance;
	this->ContactOffset = desc.contactOffset;
	this->RestOffset = desc.restOffset;
	this->GridSize = desc.gridSize;
	this->Damping = desc.damping;
	this->ExternalAcceleration = MathUtil::PxVec3ToVector3(desc.externalAcceleration);
	this->ProjectionPlaneNormal = MathUtil::PxVec3ToVector3(desc.projectionPlaneNormal);
	this->ProjectionPlaneDistance = desc.projectionPlaneDistance;
	this->ParticleMass = desc.particleMass;
	this->Restitution = desc.restitution;
	this->DynamicFriction = desc.dynamicFriction;
	this->StaticFriction = desc.staticFriction;
	this->SimulationFilterData = FilterData::ToManaged(desc.simulationFilterData);
	this->ParticleBaseFlags = ToManagedEnum(ParticleBaseFlag, desc.particleBaseFlags);
	this->ParticleReadDataFlags = ToManagedEnum(ParticleReadDataFlag, desc.particleReadDataFlags);
}
void ParticleBaseDesc::PopulateUnmanaged(PxParticleBaseDesc& desc)
{
	ActorDesc::PopulateUnmanaged(desc);

	desc.maxParticles = this->MaximumParticles;
	desc.maxMotionDistance = this->MaximumMotionDistance;
	desc.contactOffset = this->ContactOffset;
	desc.restOffset = this->RestOffset;
	desc.gridSize = this->GridSize;
	desc.damping = this->Damping;
	desc.externalAcceleration = MathUtil::Vector3ToPxVec3(this->ExternalAcceleration);
	desc.projectionPlaneNormal = MathUtil::Vector3ToPxVec3(this->ProjectionPlaneNormal);
	desc.projectionPlaneDistance = this->ProjectionPlaneDistance;
	desc.particleMass = this->ParticleMass;
	desc.restitution = this->Restitution;
	desc.dynamicFriction = this->DynamicFriction;
	desc.staticFriction = this->StaticFriction;
	desc.simulationFilterData = FilterData::ToUnmanaged(this->SimulationFilterData);
	desc.particleBaseFlags = ToUnmanagedEnum(PxParticleBaseFlag, this->ParticleBaseFlags);
	desc.particleReadDataFlags = ToUnmanagedEnum(PxParticleReadDataFlag, this->ParticleReadDataFlags);
}

void ParticleBaseDesc::SetToDefault([Optional] Nullable<TolerancesScale> scale)
{
	MaximumParticles			= 32767;
	MaximumMotionDistance		= 0.06f;
	ContactOffset				= 0.008f;
	RestOffset					= 0.004f;
	GridSize					= 0.6f;
	ParticleMass				= 0.001f;
	Damping						= 0.0f;
	ExternalAcceleration		= Vector3::Zero;
	ProjectionPlaneNormal		= Vector3::UnitZ;
	ProjectionPlaneDistance		= 0.0f;
	Restitution					= 0.5f;
	DynamicFriction				= 0.05f;
	StaticFriction				= 0.0f;

	SimulationFilterData		.SetToDefault();

	ParticleBaseFlags			= ParticleBaseFlag::Enabled;
	ParticleReadDataFlags		= ParticleReadDataFlag::PositionBuffer | ParticleReadDataFlag::FlagsBuffer;
}