#include "StdAfx.h"

#include "Particle Data.h"
#include "Physics Stream.h"
#include "Functions.h"

#include <NxParticleData.h> 

using namespace StillDesign::PhysX;

ParticleData::ParticleData()
	: BufferData( true, true )
{
	_data = new NxParticleData();
		_data->setToDefault();
	
	_data->numParticlesPtr = NULL;
}
ParticleData::ParticleData( NxParticleData* data, bool objectOwner, bool dataOwner )
	: BufferData( objectOwner, dataOwner )
{
	Debug::Assert( data != NULL );
	
	_data = data;
	
	if( _data->numParticlesPtr != NULL )
	{
		int c = *_data->numParticlesPtr;
		
		if( _data->bufferPos != NULL )
			_positionBuffer = gcnew PhysicsStream( (BYTE*)_data->bufferPos, _data->bufferPosByteStride * c );
		
		if( _data->bufferVel != NULL )
			_velocityBuffer = gcnew PhysicsStream( (BYTE*)_data->bufferVel, _data->bufferVelByteStride * c );
	
		if( _data->bufferLife != NULL )
			_lifeBuffer = gcnew PhysicsStream( (BYTE*)_data->bufferLife, _data->bufferLifeByteStride * c );
		
		if( _data->bufferDensity != NULL )
			_densityBuffer = gcnew PhysicsStream( (BYTE*)_data->bufferDensity, _data->bufferDensityByteStride * c );
		
		if( _data->bufferId != NULL )
			_idBuffer = gcnew PhysicsStream( (BYTE*)_data->bufferId, _data->bufferIdByteStride * c );
		
		if( _data->bufferFlag != NULL )
			_flagBuffer = gcnew PhysicsStream( (BYTE*)_data->bufferFlag, _data->bufferFlagByteStride * c );
		
		if( _data->bufferCollisionNormal != NULL )
			_collisionNormalBuffer = gcnew PhysicsStream( (BYTE*)_data->bufferCollisionNormal, _data->bufferCollisionNormalByteStride * c );
	}
}
ParticleData::~ParticleData()
{
	this->!ParticleData();
}
ParticleData::!ParticleData()
{
	if( this->IsDisposed )
		return;

	if( this->DataOwner )
	{
		SAFE_DELETE( _data->numParticlesPtr );
		
		void* buffers[] = 
		{
			_data->bufferPos,
			_data->bufferVel,
			_data->bufferLife,
			_data->bufferDensity,
			_data->bufferId,
			_data->bufferFlag,
			_data->bufferCollisionNormal
		};
		
		SAFE_DELETE( _data->numParticlesPtr );
		SAFE_FREE_MANY( buffers );
	}

	if( this->ObjectOwner )
	{
		SAFE_DELETE( _data );
	}
	
	_positionBuffer = nullptr;
	_velocityBuffer = nullptr;
	_lifeBuffer = nullptr;
	_densityBuffer = nullptr;
	_idBuffer = nullptr;
	_flagBuffer = nullptr;
	_collisionNormalBuffer = nullptr;
}
bool ParticleData::IsDisposed::get()
{
	return ( _data == NULL );
}

void ParticleData::SetToDefault()
{
	void* buffers[] = 
	{
		_data->numParticlesPtr,
		_data->bufferPos,
		_data->bufferVel,
		_data->bufferLife,
		_data->bufferDensity,
		_data->bufferId,
		_data->bufferFlag,
		_data->bufferCollisionNormal
	};
	
	SAFE_FREE_MANY( buffers );
	
	_data->setToDefault();
	
	_positionBuffer = nullptr;
	_velocityBuffer = nullptr;
	_lifeBuffer = nullptr;
	_densityBuffer = nullptr;
	_idBuffer = nullptr;
	_flagBuffer = nullptr;
	_collisionNormalBuffer = nullptr;
}
bool ParticleData::IsValid()
{
	return _data->isValid();
}

ParticleData^ ParticleData::FromUnmanagedPointer( NxParticleData* particleData, bool objectOwner, bool dataOwner )
{
	return gcnew ParticleData( particleData, objectOwner, dataOwner );
}
NxParticleData* ParticleData::Clone( NxParticleData particleData )
{
	NxParticleData* data = new NxParticleData();

	// We can only clone the buffers if we know how long they are
	if( particleData.numParticlesPtr != NULL )
	{
		int n = *particleData.numParticlesPtr;

		data->numParticlesPtr = new NxU32();
		*data->numParticlesPtr = n;

		// Pos
		if( particleData.bufferPos != NULL )
		{
			data->bufferPos = (NxF32*)malloc( n * particleData.bufferPosByteStride );
			memcpy( data->bufferPos, particleData.bufferPos, n * particleData.bufferPosByteStride );
		}

		// Vel
		if( particleData.bufferVel != NULL )
		{
			data->bufferVel = (NxF32*)malloc( n * particleData.bufferVelByteStride );
			memcpy( data->bufferVel, particleData.bufferVel, n * particleData.bufferVelByteStride );
		}

		// Life
		if( particleData.bufferLife != NULL )
		{
			data->bufferLife = (NxF32*)malloc( n * particleData.bufferLifeByteStride );
			memcpy( data->bufferLife, particleData.bufferLife, n * particleData.bufferLifeByteStride );
		}

		// Density
		if( particleData.bufferDensity != NULL )
		{
			data->bufferDensity = (NxF32*)malloc( n * particleData.bufferDensityByteStride );
			memcpy( data->bufferDensity, particleData.bufferDensity, n * particleData.bufferDensityByteStride );
		}

		// ID
		if( particleData.bufferId != NULL )
		{
			data->bufferId = (NxU32*)malloc( n * particleData.bufferIdByteStride );
			memcpy( data->bufferId, particleData.bufferId, n * particleData.bufferIdByteStride );
		}

		// Flag
		if( particleData.bufferFlag != NULL )
		{
			data->bufferFlag = (NxU32*)malloc( n * particleData.bufferFlagByteStride );
			memcpy( data->bufferFlag, particleData.bufferFlag, n * particleData.bufferFlagByteStride );
		}

		// Normal
		if( particleData.bufferCollisionNormal != NULL )
		{
			data->bufferCollisionNormal = (NxF32*)malloc( n * particleData.bufferCollisionNormalByteStride );
			memcpy( data->bufferCollisionNormal, particleData.bufferCollisionNormal, n * particleData.bufferCollisionNormalByteStride );
		}
	}

	if( particleData.name != NULL )
	{
		int size = sizeof(char) * strlen(particleData.name);
		char* name = (char*)malloc( size );
		strcpy_s( name, size, particleData.name );

		data->name = name;
	}

	return data;
}
ParticleData^ ParticleData::Clone( ParticleData^ particleData )
{
	if( particleData == nullptr )
		return nullptr;

	NxParticleData* clone = Clone( *particleData->UnmanagedPointer );

	return gcnew ParticleData( clone, true, true );
}

generic<typename T> PhysicsStream^ ParticleData::AllocatePositionBuffer( int numberOfParticles )
{
	return AllocatePositionBuffer( sizeof( T ) * numberOfParticles, sizeof( T ) );
}
PhysicsStream^ ParticleData::AllocatePositionBuffer( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _positionBuffer, _data->bufferPos, _data->bufferPosByteStride, NxF32* );
}

generic<typename T> PhysicsStream^ ParticleData::AllocateVelocityBuffer( int numberOfParticles )
{
	return AllocateVelocityBuffer( sizeof( T ) * numberOfParticles, sizeof( T ) );
}
PhysicsStream^ ParticleData::AllocateVelocityBuffer( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _velocityBuffer, _data->bufferVel, _data->bufferVelByteStride, NxF32* );
}

generic<typename T> PhysicsStream^ ParticleData::AllocateLifeBuffer( int numberOfParticles )
{
	return AllocateLifeBuffer( sizeof( T ) * numberOfParticles, sizeof( T ) );
}
PhysicsStream^ ParticleData::AllocateLifeBuffer( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _lifeBuffer, _data->bufferLife, _data->bufferLifeByteStride, NxF32* );
}

generic<typename T> PhysicsStream^ ParticleData::AllocateDensityBuffer( int numberOfParticles )
{
	return AllocateDensityBuffer( sizeof( T ) * numberOfParticles, sizeof( T ) );
}
PhysicsStream^ ParticleData::AllocateDensityBuffer( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _densityBuffer, _data->bufferDensity, _data->bufferDensityByteStride, NxF32* );
}

generic<typename T> PhysicsStream^ ParticleData::AllocateIdBuffer( int numberOfParticles )
{
	return AllocateIdBuffer( sizeof( T ) * numberOfParticles, sizeof( T ) );
}
PhysicsStream^ ParticleData::AllocateIdBuffer( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _idBuffer, _data->bufferId, _data->bufferIdByteStride, NxU32* );
}

generic<typename T> PhysicsStream^ ParticleData::AllocateFlagBuffer( int numberOfParticles )
{
	return AllocateFlagBuffer( sizeof( T ) * numberOfParticles, sizeof( T ) );
}
PhysicsStream^ ParticleData::AllocateFlagBuffer( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _flagBuffer, _data->bufferFlag, _data->bufferFlagByteStride, NxU32* );
}

generic<typename T> PhysicsStream^ ParticleData::AllocateCollisionNormalBuffer( int numberOfParticles )
{
	return AllocateCollisionNormalBuffer( sizeof( T ) * numberOfParticles, sizeof( T ) );
}
PhysicsStream^ ParticleData::AllocateCollisionNormalBuffer( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _collisionNormalBuffer, _data->bufferCollisionNormal, _data->bufferCollisionNormalByteStride, NxF32* );
}

void ParticleData::AllocateCommonParticleData( int numberOfParticles, ParticleData::Type types )
{
	NumberOfParticles = numberOfParticles;
	
	if( (unsigned int)(types & ParticleData::Type::Position) != 0 )
		AllocatePositionBuffer<Vector3>( numberOfParticles );
		
	if( (unsigned int)(types & ParticleData::Type::Velocity) != 0 )
		AllocateVelocityBuffer<Vector3>( numberOfParticles );
		
	if( (unsigned int)(types & ParticleData::Type::Life) != 0 )
		AllocateLifeBuffer<float>( numberOfParticles );
		
	if( (unsigned int)(types & ParticleData::Type::Density) != 0 )
		AllocateDensityBuffer<float>( numberOfParticles );
		
	if( (unsigned int)(types & ParticleData::Type::CollisionNormal) != 0 )
		AllocateCollisionNormalBuffer<Vector3>( numberOfParticles );
		
	if( (unsigned int)(types & ParticleData::Type::Flag) != 0 )
		AllocateFlagBuffer<unsigned int>( numberOfParticles );
		
	if( (unsigned int)(types & ParticleData::Type::ID) != 0 )
		AllocateIdBuffer<unsigned int >( numberOfParticles );
}

//

String^ ParticleData::Name::get()
{
	return Functions::UnmanagedToManagedString( _data->name );
}
void ParticleData::Name::set( String^ value )
{
	_data->name = Functions::ManagedToUnmanagedString( value );
}

Nullable<int> ParticleData::NumberOfParticles::get()
{
	if( _data->numParticlesPtr == NULL )
		return Nullable<int>();
	else
		return *_data->numParticlesPtr;
}
void ParticleData::NumberOfParticles::set( Nullable<int> value )
{
	if( value.HasValue == false )
	{
		SAFE_DELETE( _data->numParticlesPtr );
	}else{
		if( _data->numParticlesPtr == NULL )
			_data->numParticlesPtr = new NxU32();
		
		(*_data->numParticlesPtr) = value.Value;
	}
}

PhysicsStream^ ParticleData::PositionBuffer::get()
{
	return _positionBuffer;
}
PhysicsStream^ ParticleData::VelocityBuffer::get()
{
	return _velocityBuffer;
}
PhysicsStream^ ParticleData::LifeBuffer::get()
{
	return _lifeBuffer;
}
PhysicsStream^ ParticleData::DensityBuffer::get()
{
	return _densityBuffer;
}
PhysicsStream^ ParticleData::IDBuffer::get()
{
	return _idBuffer;
}
PhysicsStream^ ParticleData::FlagBuffer::get()
{
	return _flagBuffer;
}
PhysicsStream^ ParticleData::CollisionNormalBuffer::get()
{
	return _collisionNormalBuffer;
}

int ParticleData::PositionBufferStrideSize::get()
{
	return _data->bufferPosByteStride;
}
int ParticleData::VelocityBufferStrideSize::get()
{
	return _data->bufferVelByteStride;
}
int ParticleData::LifeBufferStrideSize::get()
{
	return _data->bufferLifeByteStride;
}
int ParticleData::DensityBufferStrideSize::get()
{
	return _data->bufferDensityByteStride;
}
int ParticleData::IDBufferStrideSize::get()
{
	return _data->bufferIdByteStride;
}
int ParticleData::FlagBufferStrideSize::get()
{
	return _data->bufferFlagByteStride;
}
int ParticleData::CollisionNormalBufferStrideSize::get()
{
	return _data->bufferCollisionNormalByteStride;
}

NxParticleData* ParticleData::UnmanagedPointer::get()
{
	return _data;
}