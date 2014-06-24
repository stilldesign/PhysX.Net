#include "StdAfx.h"
#include "ParticleReadData.h"
//#include <PxParticleReadData.h> 

ParticleReadData::ParticleReadData(PxParticleReadData* data)
	: LockedData(data)
{
}

void ParticleReadData::Unlock()
{
	this->UnmanagedPointer->unlock();
}

array<int>^ ParticleReadData::GetValidParticleBitmap()
{
	if (this->UnmanagedPointer->validParticleRange == 0)
		return nullptr;

	return Util::AsManagedArray<int>(this->UnmanagedPointer->validParticleBitmap, this->UnmanagedPointer->validParticleRange - 1);
}

array<Vector3>^ ParticleReadData::GetPositions()
{
	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	const PxVec3* p = this->UnmanagedPointer->positionBuffer.ptr();

	auto positions = Util::AsManagedArray<Vector3>(p, n);

	return positions;
}

array<Vector3>^ ParticleReadData::GetVelocities()
{
	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	const PxVec3* v = this->UnmanagedPointer->velocityBuffer.ptr();

	auto velocities = Util::AsManagedArray<Vector3>(v, n);

	return velocities;
}

array<float>^ ParticleReadData::GetRestOffsets()
{
	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	array<float>^ ret = gcnew array<float>(n);

	for (int i = 0; i < n; i++)
		ret[i] = this->UnmanagedPointer->restOffsetBuffer[i];

	return ret;
}

array<ParticleFlag>^ ParticleReadData::GetFlags()
{
	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	array<ParticleFlag>^ ret = gcnew array<ParticleFlag>(n);
	for (int i = 0; i < n; i++)
	{
		PxU16 flag = this->UnmanagedPointer->flagsBuffer[i];
		ret[i] = (ParticleFlag)flag;
	}

	return ret;
}

array<Vector3>^ ParticleReadData::GetCollisionNormals()
{
	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	const PxVec3* c = this->UnmanagedPointer->collisionNormalBuffer.ptr();

	auto collisionNormals = Util::AsManagedArray<Vector3>(c, n);

	return collisionNormals;
}

PhysX::DataAccessFlag ParticleReadData::DataAccessFlag::get()
{
	return ToManagedEnum(PhysX::DataAccessFlag, this->UnmanagedPointer->getDataAccessFlags());
}

int ParticleReadData::NumberOfValidParticles::get()
{
	return this->UnmanagedPointer->nbValidParticles;
}

int ParticleReadData::ValidParticleRange::get()
{
	return this->UnmanagedPointer->validParticleRange;
}

PxParticleReadData* ParticleReadData::UnmanagedPointer::get()
{
	return (PxParticleReadData*)LockedData::UnmanagedPointer;
}