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

	PxVec3 *p =  (PxVec3 *) malloc(n * sizeof(PxVec3));

	p = new PxVec3[n];

	for (int i = 0; i < n; i++)
		p[i] = this->UnmanagedPointer->positionBuffer[i];

	array<Vector3>^ ret = Util::AsManagedArray<Vector3>((void*)p, n);

	free(p);

	return ret;
}

array<Vector3>^ ParticleReadData::GetVelocities()
{
	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	PxVec3 *v =  (PxVec3 *) malloc(n * sizeof(PxVec3));

	v = new PxVec3[n];

	for (int i = 0; i < n; i++)
		v[i] = this->UnmanagedPointer->velocityBuffer[i];

	array<Vector3>^ ret = Util::AsManagedArray<Vector3>((void*)v, n);

	free(v);

	return ret;
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

	PxParticleFlags *f =  (PxParticleFlags *) malloc(n * sizeof(PxParticleFlags));

	f = new PxParticleFlags[n];

	for (int i = 0; i < n; i++)
		f[i] = this->UnmanagedPointer->flagsBuffer[i];

	array<ParticleFlag>^ ret = Util::AsManagedArray<ParticleFlag>((void*)f, n);

	free(f);

	return ret;
}

array<Vector3>^ ParticleReadData::GetCollisionNormals()
{
	const int n = this->UnmanagedPointer->nbValidParticles;

	if (n <= 0)
		return nullptr;

	PxVec3 *c =  (PxVec3 *) malloc(n * sizeof(PxVec3));

	c = new PxVec3[n];

	for (int i = 0; i < n; i++)
		c[i] = this->UnmanagedPointer->collisionNormalBuffer[i];

	array<Vector3>^ ret = Util::AsManagedArray<Vector3>((void*)c, n);

	free(c);

	return ret;
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