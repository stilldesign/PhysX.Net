#include "StdAfx.h"

#include "Particle Id Data.h"
#include "Functions.h"
#include "Physics Stream.h"

using namespace StillDesign::PhysX;
ParticleIdData::ParticleIdData()
{
	_data = new NxParticleIdData();
		_data->numIdsPtr = new NxU32();
}
ParticleIdData::ParticleIdData( NxParticleIdData* data )
{
	Debug::Assert( data != NULL );
	
	_data = data;
	
	if( data->numIdsPtr != NULL )
	{
		if( *data->numIdsPtr < 0 )
			throw gcnew PhysXException( "Number of Ids cannot be less than 0" );
		
		if( data->bufferId != NULL )
			_idsStream = gcnew PhysicsStream( (BYTE*)data->bufferId, *data->numIdsPtr * data->bufferIdByteStride );
	}
}
ParticleIdData::~ParticleIdData()
{
	this->!ParticleIdData();
}
ParticleIdData::!ParticleIdData()
{
	if( this->IsDisposed )
		return;
	
	OnDisposing( this, nullptr );
	
	SAFE_DELETE( _data->numIdsPtr );
	
	SAFE_DELETE( _data->bufferId );
	SAFE_DELETE( _data );
	
	_idsStream = nullptr;
	
	OnDisposed( this, nullptr );
}
bool ParticleIdData::IsDisposed::get()
{
	return ( _data == NULL );
}

void ParticleIdData::SetToDefault()
{
	SAFE_DELETE( _data->bufferId );
	_idsStream = nullptr;
	
	this->NumberOfIds = 0;
	
	_data->bufferIdByteStride = 0;
	_data->name = NULL;
}
bool ParticleIdData::IsValid()
{
	return _data->isValid();
}

PhysicsStream^ ParticleIdData::AllocateIds( int size, int strideSize )
{
	StdPhysicsStreamAllocEx( _idsStream, _data->bufferId, strideSize, NxU32* );
}
generic<typename T> PhysicsStream^ ParticleIdData::AllocateIds( int numberOfIds )
{
	return AllocateIds( sizeof( T ) * numberOfIds, sizeof( T ) );
}

String^ ParticleIdData::Name::get()
{
	return Functions::UnmanagedToManagedString( _data->name );
}
void ParticleIdData::Name::set( String^ value )
{
	_data->name = Functions::ManagedToUnmanagedString( value );
}

int ParticleIdData::NumberOfIds::get()
{
	return *_data->numIdsPtr;
}
void ParticleIdData::NumberOfIds::set( int value )
{
	*_data->numIdsPtr = value;
}

int ParticleIdData::StrideSize::get()
{
	return _data->bufferIdByteStride;
}

NxParticleIdData* ParticleIdData::UnmanagedPointer::get()
{
	return _data;
}