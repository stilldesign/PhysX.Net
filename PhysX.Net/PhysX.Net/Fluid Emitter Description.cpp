#include "StdAfx.h"

#include "Fluid Emitter Description.h"
#include "Math.h"
#include "Functions.h"
#include "Shape.h"
#include "Scene.h"
#include "Shape.h"

using namespace StillDesign::PhysX;

FluidEmitterDescription::FluidEmitterDescription()
{
	_fluidEmitterDesc = new NxFluidEmitterDesc();
}
FluidEmitterDescription::FluidEmitterDescription( NxFluidEmitterDesc* emitterDesc )
{
	Debug::Assert( emitterDesc != NULL );
	
	_fluidEmitterDesc = emitterDesc;
	
	_shape = ObjectCache::GetObject<StillDesign::PhysX::Shape^>( (intptr_t)emitterDesc->frameShape );
}
FluidEmitterDescription::~FluidEmitterDescription()
{
	this->!FluidEmitterDescription();
}
FluidEmitterDescription::!FluidEmitterDescription()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );

	SAFE_DELETE( _fluidEmitterDesc );
	
	_shape = nullptr;
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool FluidEmitterDescription::IsDisposed::get()
{
	return ( _fluidEmitterDesc == NULL );
}

void FluidEmitterDescription::SetToDefault()
{
	_fluidEmitterDesc->setToDefault();
	
	_shape = nullptr;
	_userData = nullptr;
}
bool FluidEmitterDescription::IsValid()
{
	return _fluidEmitterDesc->isValid();
}

String^ FluidEmitterDescription::Name::get()
{
	return ToManagedString( _fluidEmitterDesc->name );
}
void FluidEmitterDescription::Name::set( String^ value )
{
	_fluidEmitterDesc->name = ToUnmanagedString( value );
}

Matrix FluidEmitterDescription::RelativePose::get()
{
	return Math::Mat34ToMatrix( &_fluidEmitterDesc->relPose );
}
void FluidEmitterDescription::RelativePose::set( Matrix value )
{
	_fluidEmitterDesc->relPose = Math::MatrixToMat34( value );
}

StillDesign::PhysX::Shape^ FluidEmitterDescription::FrameShape::get()
{
	return _shape;
}
void FluidEmitterDescription::FrameShape::set( StillDesign::PhysX::Shape^ value )
{
	_shape = value;
	
	if( value == nullptr )
		_fluidEmitterDesc->frameShape = NULL;
	else
		_fluidEmitterDesc->frameShape = value->UnmanagedPointer;
}

EmitterType FluidEmitterDescription::Type::get()
{
	return (EmitterType)_fluidEmitterDesc->type;
}
void FluidEmitterDescription::Type::set( EmitterType value )
{
	_fluidEmitterDesc->type = (NxEmitterType)value;
}

int FluidEmitterDescription::MaximumParticles::get()
{
	return _fluidEmitterDesc->maxParticles;
}
void FluidEmitterDescription::MaximumParticles::set( int value )
{
	_fluidEmitterDesc->maxParticles = value;
}

EmitterShape FluidEmitterDescription::Shape::get()
{
	return (EmitterShape)_fluidEmitterDesc->shape;
}
void FluidEmitterDescription::Shape::set( EmitterShape value )
{
	_fluidEmitterDesc->shape = (NxEmitterShape)value;
}

float FluidEmitterDescription::DimensionX::get()
{
	return _fluidEmitterDesc->dimensionX;
}
void FluidEmitterDescription::DimensionX::set( float value )
{
	_fluidEmitterDesc->dimensionX = value;
}

float FluidEmitterDescription::DimensionY::get()
{
	return _fluidEmitterDesc->dimensionY;
}
void FluidEmitterDescription::DimensionY::set( float value )
{
	_fluidEmitterDesc->dimensionY = value;
}

Vector3 FluidEmitterDescription::RandomPosition::get()
{
	return Math::NxVec3ToVector3( _fluidEmitterDesc->randomPos );
}
void FluidEmitterDescription::RandomPosition::set( Vector3 value )
{
	_fluidEmitterDesc->randomPos = Math::Vector3ToNxVec3( value );
}

float FluidEmitterDescription::RandomAngle::get()
{
	return _fluidEmitterDesc->randomAngle;
}
void FluidEmitterDescription::RandomAngle::set( float value )
{
	_fluidEmitterDesc->randomAngle = value;
}

float FluidEmitterDescription::FluidVelocityMagnitude::get()
{
	return _fluidEmitterDesc->fluidVelocityMagnitude;
}
void FluidEmitterDescription::FluidVelocityMagnitude::set( float value )
{
	_fluidEmitterDesc->fluidVelocityMagnitude = value;
}

float FluidEmitterDescription::Rate::get()
{
	return _fluidEmitterDesc->rate;
}
void FluidEmitterDescription::Rate::set( float value )
{
	_fluidEmitterDesc->rate = value;
}

float FluidEmitterDescription::ParticleLifetime::get()
{
	return _fluidEmitterDesc->particleLifetime;
}
void FluidEmitterDescription::ParticleLifetime::set( float value )
{
	_fluidEmitterDesc->particleLifetime = value;
}

float FluidEmitterDescription::RepulsionCoefficient::get()
{
	return _fluidEmitterDesc->repulsionCoefficient;
}
void FluidEmitterDescription::RepulsionCoefficient::set( float value )
{
	_fluidEmitterDesc->repulsionCoefficient = value;
}

FluidEmitterFlag FluidEmitterDescription::Flags::get()
{
	return (FluidEmitterFlag)_fluidEmitterDesc->flags;
}
void FluidEmitterDescription::Flags::set( FluidEmitterFlag value )
{
	_fluidEmitterDesc->flags = (NxFluidEmitterFlag)value;
}

Object^ FluidEmitterDescription::UserData::get()
{
	return _userData;
}
void FluidEmitterDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxFluidEmitterDesc* FluidEmitterDescription::UnmanagedPointer::get()
{
	return _fluidEmitterDesc;
}