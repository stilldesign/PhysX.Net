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
	auto buffer = this->UnmanagedPointer->positionBuffer;

	if (buffer.ptr() == NULL)
		return nullptr;

	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	auto positions = gcnew array<Vector3>(n);
	
	for (size_t i = 0; i < n; i++)
	{
		PxVec3 p = buffer[i];

		positions[i] = Vector3(p.x, p.y, p.z);
	}

	return positions;
}

array<Vector3>^ ParticleReadData::GetVelocities()
{
	auto buffer = this->UnmanagedPointer->velocityBuffer;

	if (buffer.ptr() == NULL)
		return nullptr;

	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	auto velocities = gcnew array<Vector3>(n);

	for (size_t i = 0; i < n; i++)
	{
		PxVec3 v = buffer[i];

		velocities[i] = Vector3(v.x, v.y, v.z);
	}

	return velocities;
}

array<float>^ ParticleReadData::GetRestOffsets()
{
	auto buffer = this->UnmanagedPointer->restOffsetBuffer;

	if (buffer.ptr() == NULL)
		return nullptr;

	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	auto restOffsets = gcnew array<float>(n);

	for (int i = 0; i < n; i++)
	{
		restOffsets[i] = buffer[i];
	}

	return restOffsets;
}

array<ParticleFlag>^ ParticleReadData::GetFlags()
{
	auto buffer = this->UnmanagedPointer->flagsBuffer;

	if (buffer.ptr() == NULL)
		return nullptr;

	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	auto flags = gcnew array<ParticleFlag>(n);

	for (int i = 0; i < n; i++)
	{
		PxU16 flag = buffer[i];

		flags [i] = (ParticleFlag)flag;
	}

	return flags;
}

array<Vector3>^ ParticleReadData::GetCollisionNormals()
{
	auto buffer = this->UnmanagedPointer->collisionNormalBuffer;

	if (buffer.ptr() == NULL)
		return nullptr;

	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	auto collisionNormals = gcnew array<Vector3>(n);

	for (size_t i = 0; i < n; i++)
	{
		PxVec3 n = buffer[i];

		collisionNormals[i] = Vector3(n.x, n.y, n.z);
	}

	return collisionNormals;
}

array<Vector3>^ ParticleReadData::GetCollisionVelocities()
{
	auto buffer = this->UnmanagedPointer->collisionVelocityBuffer;

	if (buffer.ptr() == NULL)
		return nullptr;

	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	auto collisionVelocities = gcnew array<Vector3>(n);

	for (size_t i = 0; i < n; i++)
	{
		PxVec3 n = buffer[i];

		collisionVelocities[i] = Vector3(n.x, n.y, n.z);
	}

	return collisionVelocities;
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