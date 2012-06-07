#include "StdAfx.h"
#include "ParticleReadData.h"
#include <PxParticleReadData.h> 

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
	//return Util::AsManagedArray<int>(this->UnmanagedPointer->validParticleBitmap(), 
	throw gcnew NotImplementedException();
}
void ParticleReadData::SetValidParticleBitmap(array<int>^ bitmap)
{
	throw gcnew NotImplementedException();
}

array<Vector3>^ ParticleReadData::GetPositionBuffer()
{
	return Util::AsManagedArray<Vector3>((void*)this->UnmanagedPointer->positionBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}
void ParticleReadData::SetPositionBuffer(array<Vector3>^ value)
{
	Util::AsUnmanagedArray(value, (void*)this->UnmanagedPointer->positionBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}

array<Vector3>^ ParticleReadData::GetVelocityBuffer()
{
	return Util::AsManagedArray<Vector3>((void*)this->UnmanagedPointer->velocityBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}
void ParticleReadData::SetVelocityBuffer(array<Vector3>^ value)
{
	Util::AsUnmanagedArray(value, (void*)this->UnmanagedPointer->velocityBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}

array<float>^ ParticleReadData::GetRestOffsetBuffer()
{
	return Util::AsManagedArray<float>((void*)this->UnmanagedPointer->restOffsetBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}
void ParticleReadData::SetRestOffsetBuffer(array<float>^ value)
{
	Util::AsUnmanagedArray(value, (void*)this->UnmanagedPointer->restOffsetBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}

array<ParticleFlag>^ ParticleReadData::GetFlagsBuffer()
{
	return Util::AsManagedArray<ParticleFlag>((void*)this->UnmanagedPointer->flagsBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}
void ParticleReadData::SetFlagsBuffer(array<ParticleFlag>^ value)
{
	Util::AsUnmanagedArray(value, (void*)this->UnmanagedPointer->flagsBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}

array<Vector3>^ ParticleReadData::GetCollisionNormalBuffer()
{
	return Util::AsManagedArray<Vector3>((void*)this->UnmanagedPointer->collisionNormalBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}
void ParticleReadData::SetCollisionNormalBuffer(array<Vector3>^ value)
{
	Util::AsUnmanagedArray(value, (void*)this->UnmanagedPointer->collisionNormalBuffer.ptr(), this->UnmanagedPointer->numValidParticles);
}

PhysX::DataAccessFlag ParticleReadData::DataAccessFlag::get()
{
	return ToManagedEnum(PhysX::DataAccessFlag, this->UnmanagedPointer->getDataAccessFlags());
}

int ParticleReadData::NumberOfValidParticles::get()
{
	return this->UnmanagedPointer->numValidParticles;
}
void ParticleReadData::NumberOfValidParticles::set(int value)
{
	this->UnmanagedPointer->numValidParticles = value;
}

int ParticleReadData::ValidParticleRange::get()
{
	return this->UnmanagedPointer->validParticleRange;
}
void ParticleReadData::ValidParticleRange::set(int value)
{
	this->UnmanagedPointer->validParticleRange = value;
}

PxParticleReadData* ParticleReadData::UnmanagedPointer::get()
{
	return (PxParticleReadData*)LockedData::UnmanagedPointer;
}