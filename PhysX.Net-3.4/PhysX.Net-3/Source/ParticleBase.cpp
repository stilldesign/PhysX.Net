#include "StdAfx.h"
#include "ParticleBase.h"
#include "Actor.h"
#include "FilterData.h"
#include "ParticleReadData.h"
#include "ParticleCreationData.h"
#include "Physics.h"

ParticleBase::ParticleBase(PxParticleBase* particleBase, PhysX::Physics^ owner)
	: Actor(particleBase, owner)
{
	
}

ParticleReadData^ ParticleBase::LockParticleReadData()
{
	return gcnew ParticleReadData(this->UnmanagedPointer->lockParticleReadData());
}

int ParticleBase::CreateParticles(ParticleCreationData^ creationData)
{
	ThrowIfNull(creationData, "creationData");

	PxParticleCreationData data = ParticleCreationData::ToUnmanaged(creationData);

	if (!data.isValid())
		throw gcnew ArgumentException("Particle creation data is invalid", "creationData");

	return this->UnmanagedPointer->createParticles(data);
}

void ParticleBase::ReleaseParticles()
{
	this->UnmanagedPointer->releaseParticles();
}
void ParticleBase::ReleaseParticles(int numberOfParticles, [Optional] array<PxU32>^ indexBuffer)
{
	ThrowIfNull(indexBuffer, "indexBuffer");
	
	if (indexBuffer->Length == 0)
		return;

	pin_ptr<PxU32> b = &indexBuffer[0];
	const PxStrideIterator<PxU32> i(b);
	
	this->UnmanagedPointer->releaseParticles(numberOfParticles, i);
}

void ParticleBase::SetPositions(array<Vector3>^ positions, array<int>^ indexBuffer)
{
	ThrowIfNull(positions, "positions");
	ThrowIfNull(indexBuffer, "indexBuffer");
	if (indexBuffer->Length == 0)
		return;

	PxVec3* p = (PxVec3*)malloc(sizeof(PxVec3) * positions->Length);
	Util::AsUnmanagedArray(positions, p);
	const PxStrideIterator<PxVec3> pos(p);

	pin_ptr<int> b = &indexBuffer[0];
	const PxStrideIterator<PxU32> i((PxU32*)b);

	this->UnmanagedPointer->setPositions(positions->Length, i, pos);

	free(p);
}

void ParticleBase::SetVelocities(array<Vector3>^ velocities, array<int>^ indexBuffer)
{
	ThrowIfNull(velocities, "velocities");
	ThrowIfNull(indexBuffer, "indexBuffer");
	if (indexBuffer->Length == 0)
		return;

	PxVec3* v = (PxVec3*)malloc(sizeof(PxVec3) * velocities->Length);
	Util::AsUnmanagedArray(velocities, v);
	const PxStrideIterator<PxVec3> vel(v);

	pin_ptr<int> b = &indexBuffer[0];
	const PxStrideIterator<PxU32> i((PxU32*)b);

	this->UnmanagedPointer->setVelocities(velocities->Length, i, vel);

	free(v);
}

void ParticleBase::SetRestOffsets(array<Vector3>^ restOffsets, array<int>^ indexBuffer)
{
	ThrowIfNull(restOffsets, "restOffsets");
	ThrowIfNull(indexBuffer, "indexBuffer");
	if (indexBuffer->Length == 0)
		return;

	float* r = (float*)malloc(sizeof(float) * restOffsets->Length);
	Util::AsUnmanagedArray(restOffsets, r);
	const PxStrideIterator<float> rest(r);

	pin_ptr<int> b = &indexBuffer[0];
	const PxStrideIterator<PxU32> i((PxU32*)b);

	this->UnmanagedPointer->setRestOffsets(restOffsets->Length, i, rest);

	free(r);
}

void ParticleBase::AddForces(array<Vector3>^ forces, array<int>^ indexBuffer, ForceMode forceMode)
{
	ThrowIfNull(forces, "forces");
	ThrowIfNull(indexBuffer, "indexBuffer");
	if (indexBuffer->Length == 0)
		return;

	PxVec3* f = (PxVec3*)malloc(sizeof(PxVec3) * forces->Length);
	Util::AsUnmanagedArray(forces, f);
	const PxStrideIterator<PxVec3> fi(f);

	pin_ptr<int> b = &indexBuffer[0];
	const PxStrideIterator<PxU32> i((PxU32*)b);

	this->UnmanagedPointer->addForces(forces->Length, i, fi, ToUnmanagedEnum(PxForceMode, forceMode));

	free(f);
}

float ParticleBase::Damping::get()
{
	return this->UnmanagedPointer->getDamping();
}
void ParticleBase::Damping::set(float value)
{
	this->UnmanagedPointer->setDamping(value);
}

Vector3 ParticleBase::ExternalAcceleration::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getExternalAcceleration());
}
void ParticleBase::ExternalAcceleration::set(Vector3 value)
{
	this->UnmanagedPointer->setExternalAcceleration(MathUtil::Vector3ToPxVec3(value));
}

Plane ParticleBase::ProjectionPlane::get()
{
	PxVec3 n;
	float d;

	this->UnmanagedPointer->getProjectionPlane(n, d);

	return Plane(MathUtil::PxVec3ToVector3(n), d);
}
void ParticleBase::ProjectionPlane::set(Plane value)
{
	this->UnmanagedPointer->setProjectionPlane(MathUtil::Vector3ToPxVec3(value.Normal), value.D);
}

float ParticleBase::ParticleMass::get()
{
	return this->UnmanagedPointer->getParticleMass();
}
void ParticleBase::ParticleMass::set(float value)
{
	this->UnmanagedPointer->setParticleMass(value);
}

float ParticleBase::Restitution::get()
{
	return this->UnmanagedPointer->getRestitution();
}
void ParticleBase::Restitution::set(float value)
{
	if (value < 0 || value > 1)
		throw gcnew ArgumentOutOfRangeException("value", "Restitution must be between 0 and 1 inc.");

	this->UnmanagedPointer->setRestitution(value);
}

float ParticleBase::DynamicFriction::get()
{
	return this->UnmanagedPointer->getDynamicFriction();
}
void ParticleBase::DynamicFriction::set(float value)
{
	if (value < 0 || value > 1)
		throw gcnew ArgumentOutOfRangeException("value", "Dynamic friction must be between 0 and 1 inc.");

	this->UnmanagedPointer->setDynamicFriction(value);
}

float ParticleBase::StaticFriction::get()
{
	return this->UnmanagedPointer->getStaticFriction();
}
void ParticleBase::StaticFriction::set(float value)
{
	this->UnmanagedPointer->setStaticFriction(value);
}

PhysX::FilterData ParticleBase::SimulationFilterData::get()
{
	return PhysX::FilterData::ToManaged(this->UnmanagedPointer->getSimulationFilterData());
}
void ParticleBase::SimulationFilterData::set(PhysX::FilterData value)
{
	this->UnmanagedPointer->setSimulationFilterData(PhysX::FilterData::ToUnmanaged(value));
}

int ParticleBase::MaximumParticles::get()
{
	return this->UnmanagedPointer->getMaxParticles();
}

float ParticleBase::MaximumMotionDistance::get()
{
	return this->UnmanagedPointer->getMaxMotionDistance();
}

float ParticleBase::RestOffset::get()
{
	return this->UnmanagedPointer->getRestOffset();
}

float ParticleBase::ContactOffset::get()
{
	return this->UnmanagedPointer->getContactOffset();
}

float ParticleBase::GridSize::get()
{
	return this->UnmanagedPointer->getGridSize();
}

PhysX::ParticleReadDataFlag ParticleBase::ParticleReadDataFlags::get()
{
	return ToManagedEnum(PhysX::ParticleReadDataFlag, this->UnmanagedPointer->getParticleReadDataFlags());
}

ParticleBaseFlag ParticleBase::Flags::get()
{
	return ToManagedEnum(ParticleBaseFlag, this->UnmanagedPointer->getParticleBaseFlags());
}
void ParticleBase::Flags::set(ParticleBaseFlag value)
{
	//this->UnmanagedPointer->setParticleBaseFlags(ToUnmanagedEnum(PxParticleBaseFlag, value));
}

PxParticleBase* ParticleBase::UnmanagedPointer::get()
{
	return (PxParticleBase*)Actor::UnmanagedPointer;
}