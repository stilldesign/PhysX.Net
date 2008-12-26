#include "StdAfx.h"

#include "Particle Update Data.h"
#include "Physics Stream.h"

#include <NxParticleUpdateData.h> 

using namespace StillDesign::PhysX;

ParticleUpdateData::ParticleUpdateData()
{
	
}
ParticleUpdateData::~ParticleUpdateData()
{
	this->!ParticleUpdateData();
}
ParticleUpdateData::!ParticleUpdateData()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	SAFE_DELETE( _updateData->bufferForce );
	SAFE_DELETE( _updateData->bufferFlag );
	SAFE_DELETE( _updateData->bufferId );
	
	SAFE_DELETE( _updateData );
	
	OnDisposed( this, nullptr );
}
bool ParticleUpdateData::IsDisposed::get()
{
	return ( _updateData == NULL );
}

void ParticleUpdateData::SetToDefault()
{
	SAFE_DELETE( _updateData->bufferForce );
	SAFE_DELETE( _updateData->bufferFlag );
	SAFE_DELETE( _updateData->bufferId );
	
	_forceStream = nullptr;
	_flagsStream = nullptr;
	_idsStream = nullptr;
	
	_updateData->setToDefault();
}
bool ParticleUpdateData::IsValid()
{
	return _updateData->isValid();
}

PhysicsStream^ ParticleUpdateData::AllocateForcesStream( int size, int strideSize )
{
	StdPhysicsStreamAlloc2( _forceStream, _updateData->bufferForce, strideSize, NxF32* );
}
generic<typename T> PhysicsStream^ ParticleUpdateData::AllocateForcesStream( int numberOfForces )
{
	return AllocateForcesStream( sizeof( T ) * numberOfForces, sizeof( T ) );
}

PhysicsStream^ ParticleUpdateData::AllocateFlagsStream( int size, int strideSize )
{
	StdPhysicsStreamAlloc2( _flagsStream, _updateData->bufferFlag, strideSize, NxU32* );
}
generic<typename T> PhysicsStream^ ParticleUpdateData::AllocateFlagsStream( int numberOfFlags )
{
	return AllocateFlagsStream( numberOfFlags * sizeof( T ), sizeof( T ) );
}

PhysicsStream^ ParticleUpdateData::AllocateIdsStream( int size, int strideSize )
{
	StdPhysicsStreamAlloc2( _idsStream, _updateData->bufferId, strideSize, NxU32* );
}
generic<typename T> PhysicsStream^ ParticleUpdateData::AllocateIdsStream( int numberOfIds )
{
	return AllocateIdsStream( numberOfIds * sizeof( T ), sizeof( T ) );
}

StillDesign::PhysX::ForceMode ParticleUpdateData::ForceMode::get()
{
	return (StillDesign::PhysX::ForceMode)_updateData->forceMode;
}
void ParticleUpdateData::ForceMode::set( StillDesign::PhysX::ForceMode value )
{
	_updateData->forceMode = (NxForceMode)value;
}

int ParticleUpdateData::NumberOfUpdates::get()
{
	return _updateData->numUpdates;
}
void ParticleUpdateData::NumberOfUpdates::set( int value )
{
	_updateData->numUpdates = value;
}

PhysicsStream^ ParticleUpdateData::ForceStream::get()
{
	return _forceStream;
}

PhysicsStream^ ParticleUpdateData::FlagsStream::get()
{
	return _flagsStream;
}

PhysicsStream^ ParticleUpdateData::IdsStream::get()
{
	return _idsStream;
}

NxParticleUpdateData* ParticleUpdateData::UnmanagedPointer::get()
{
	return _updateData;
}