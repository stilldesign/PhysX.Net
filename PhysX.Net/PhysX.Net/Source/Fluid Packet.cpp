#include "StdAfx.h"

#include "Fluid Packet.h"
#include "Bounds.h"

#include <NxFluidPacketData.h> 

using namespace StillDesign::PhysX;

FluidPacket::FluidPacket()
{
	_fluidPacket = new NxFluidPacket();
}

FluidPacket::FluidPacket( NxFluidPacket* fluidPacket )
{
	Debug::Assert( fluidPacket != NULL );
	
	_fluidPacket = fluidPacket;
}
FluidPacket::~FluidPacket()
{
	this->!FluidPacket();
}
FluidPacket::!FluidPacket()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	SAFE_DELETE( _fluidPacket );
	
	OnDisposed( this, nullptr );
}
bool FluidPacket::IsDisposed::get()
{
	return ( _fluidPacket == NULL );
}

Bounds3 FluidPacket::AxisAlignedBoundingBox::get()
{
	return (Bounds3)_fluidPacket->aabb;
}
void FluidPacket::AxisAlignedBoundingBox::set( Bounds3 value )
{
	_fluidPacket->aabb = (NxBounds3)value;
}

int FluidPacket::FirstParticleIndex::get()
{
	return _fluidPacket->firstParticleIndex;
}
void FluidPacket::FirstParticleIndex::set( int value )
{
	_fluidPacket->firstParticleIndex = value;
}

int FluidPacket::NumberOfParticles::get()
{
	return _fluidPacket->numParticles;
}
void FluidPacket::NumberOfParticles::set( int value )
{
	_fluidPacket->numParticles = value;
}

int FluidPacket::PacketId::get()
{
	return _fluidPacket->packetID;
}
void FluidPacket::PacketId::set( int value )
{
	_fluidPacket->packetID = value;
}