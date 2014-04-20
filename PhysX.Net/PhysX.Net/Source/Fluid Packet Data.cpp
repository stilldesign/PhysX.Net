#include "StdAfx.h"

#include "Fluid Packet Data.h"
#include "Physics Stream.h"

using namespace StillDesign::PhysX;

FluidPacketData::FluidPacketData()
	: BufferData( true, true )
{
	_fluidPacketData = new NxFluidPacketData();
	Debug::Assert( _fluidPacketData != NULL );
	
	_fluidPacketData->numFluidPacketsPtr = new NxU32();
	Debug::Assert( _fluidPacketData->numFluidPacketsPtr != NULL );
}
FluidPacketData::FluidPacketData( NxFluidPacketData* data, bool objectOwner, bool dataOwner )
	: BufferData( objectOwner, dataOwner )
{
	Debug::Assert( data != NULL );

	if( data->numFluidPacketsPtr != NULL )
	{
		if( *data->numFluidPacketsPtr < 0 )
			throw gcnew PhysXException( "Number of fluid packets cannot be less than 0" );
		
		if( data->bufferFluidPackets != NULL )
			_packetsStream = gcnew PhysicsStream( (BYTE*)data->bufferFluidPackets, *data->numFluidPacketsPtr * sizeof( unsigned int ) );
	}
}
FluidPacketData::~FluidPacketData()
{
	this->!FluidPacketData();
}
FluidPacketData::!FluidPacketData()
{
	if( this->IsDisposed )
		return;
	
	OnDisposing( this, EventArgs::Empty );

	if( this->DataOwner )
	{
		if( _fluidPacketData->numFluidPacketsPtr != NULL )
			delete _fluidPacketData->numFluidPacketsPtr;
	}
	
	if( this->ObjectOwner )
	{
		SAFE_DELETE( _fluidPacketData );
	}
	
	_packetsStream = nullptr;
	
	OnDisposed( this, EventArgs::Empty );
}

bool FluidPacketData::IsDisposed::get()
{
	return ( _fluidPacketData == NULL );
}

FluidPacketData^ FluidPacketData::Clone( FluidPacketData^ data )
{
	if( data == nullptr )
		return nullptr;

	if( data->UnmanagedPointer == NULL )
		return gcnew FluidPacketData();
	else
		return gcnew FluidPacketData( Clone( *data->UnmanagedPointer ), true, true );
}
NxFluidPacketData* FluidPacketData::Clone( NxFluidPacketData data )
{
	NxFluidPacketData* d = new NxFluidPacketData();

	if( data.numFluidPacketsPtr != NULL )
	{
		int n = *data.numFluidPacketsPtr;

		*d->numFluidPacketsPtr = n;

		int size = sizeof(NxFluidPacket) * n;

		d->bufferFluidPackets = (NxFluidPacket*)malloc( size );
		memcpy( d->bufferFluidPackets, data.bufferFluidPackets, size );
	}

	return d;
}

void FluidPacketData::SetToDefault()
{
	SAFE_DELETE( _fluidPacketData->bufferFluidPackets );
	_packetsStream = nullptr;
	
	_fluidPacketData->setToDefault();
}
bool FluidPacketData::IsValid()
{
	return _fluidPacketData->isValid();
}

PhysicsStream^ FluidPacketData::AllocateFluidPacketData( int numberOfFluidPackets )
{
	if( numberOfFluidPackets < 0 )
		throw gcnew ArgumentOutOfRangeException( "numberOfFluidPackets" );
	
	int strideSize = sizeof( NxFluidPacket );
	int size = numberOfFluidPackets * strideSize;
	
	StdPhysicsStreamAllocEx( _packetsStream, _fluidPacketData->bufferFluidPackets, strideSize, NxFluidPacket* );
}

PhysicsStream^ FluidPacketData::FluidPackets::get()
{
	return _packetsStream;
}
int FluidPacketData::NumberOfFluidPackets::get()
{
	return *_fluidPacketData->numFluidPacketsPtr;
}

NxFluidPacketData* FluidPacketData::UnmanagedPointer::get()
{
	return _fluidPacketData;
}