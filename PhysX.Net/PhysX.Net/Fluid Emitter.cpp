#include "StdAfx.h"

#include "Fluid Emitter.h"
#include "Math.h"
#include "Functions.h"
#include "Shape.h"
#include "Fluid.h"
#include "Fluid Emitter Description.h"
#include "Scene.h"

#include <NxFluid.h> 
#include <NxFluidEmitter.h> 

using namespace StillDesign::PhysX;

FluidEmitter::FluidEmitter( NxFluidEmitter* emitter )
{
	Debug::Assert( emitter != NULL );
	
	_fluidEmitter = emitter;
	
	ObjectCache::Add( (intptr_t)emitter, this );
	
	_fluid = ObjectCache::GetObject<StillDesign::PhysX::Fluid^>( (intptr_t)(&emitter->getFluid()) );
	
	if( emitter->getFrameShape() != NULL )
		_shape = ObjectCache::GetObject<StillDesign::PhysX::Shape^>( (intptr_t)emitter->getFrameShape() );
}

FluidEmitter::~FluidEmitter()
{
	this->!FluidEmitter();
}
FluidEmitter::!FluidEmitter()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	_fluid->UnmanagedPointer->releaseEmitter( *_fluidEmitter );
	
	_fluidEmitter = NULL;
	
	_fluid = nullptr;
	_shape = nullptr;
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool FluidEmitter::IsDisposed::get()
{
	return (_fluidEmitter == NULL);
}

FluidEmitterDescription^ FluidEmitter::SaveToDescription()
{
	NxFluidEmitterDesc* desc = new NxFluidEmitterDesc();
	if( _fluidEmitter->saveToDesc( *desc ) == false )
	{
		delete desc;
		return nullptr;
	}
	
	Shape^ frameShape;
	if( _fluidEmitter->getFrameShape() != NULL )
		frameShape = ObjectCache::GetObject<Shape^>( (intptr_t)_fluidEmitter->getFrameShape() );
	else
		frameShape = nullptr;
	
	FluidEmitterDescription^ d = gcnew FluidEmitterDescription( desc );
		d->UserData = this->UserData;
		d->FrameShape = frameShape;
	
	return d;
}
bool FluidEmitter::LoadFromDescription( FluidEmitterDescription^ description )
{
	if( description == nullptr )
		throw gcnew ArgumentNullException( "description" );
	
	return _fluidEmitter->loadFromDesc( *description->UnmanagedPointer );
}

bool FluidEmitter::GetFlag( FluidEmitterFlag flag )
{
	return _fluidEmitter->getFlag( (NxFluidEmitterFlag)flag );
}
void FluidEmitter::SetFlag( FluidEmitterFlag flag, bool value )
{
	_fluidEmitter->setFlag( (NxFluidEmitterFlag)flag, value );
}
bool FluidEmitter::GetShape( EmitterShape shape )
{
	return _fluidEmitter->getShape( (NxEmitterShape)shape );
}
bool FluidEmitter::GetType( EmitterType type )
{
	return _fluidEmitter->getType( (NxEmitterType)type );
}

void FluidEmitter::ResetEmission( int maximumParticles )
{
	_fluidEmitter->resetEmission( maximumParticles );
}

//

StillDesign::PhysX::Fluid^ FluidEmitter::Fluid::get()
{
	return _fluid;
}

String^ FluidEmitter::Name::get()
{
	return Functions::UnmanagedToManagedString( _fluidEmitter->getName() );
}
void FluidEmitter::Name::set( String^ value )
{
	_fluidEmitter->setName( Functions::ManagedToUnmanagedString( value ) );
}

int FluidEmitter::NumberOfParticlesEmitted::get()
{
	return _fluidEmitter->getNbParticlesEmitted();
}

Matrix FluidEmitter::GlobalPose::get()
{
	return Math::Mat34ToMatrix( &_fluidEmitter->getGlobalPose() );
}
void FluidEmitter::GlobalPose::set( Matrix value )
{
	_fluidEmitter->setGlobalPose( Math::MatrixToMat34( value ) );
}
Vector3 FluidEmitter::GlobalPosition::get()
{
	return Math::NxVec3ToVector3( _fluidEmitter->getGlobalPosition() );
}
void FluidEmitter::GlobalPosition::set( Vector3 value )
{
	_fluidEmitter->setGlobalPosition( Math::Vector3ToNxVec3( value ) );
}
Matrix FluidEmitter::GlobalOrientation::get()
{
	return Math::Mat33ToMatrix( &_fluidEmitter->getGlobalOrientation() );
}
void FluidEmitter::GlobalOrientation::set( Matrix value )
{
	_fluidEmitter->setGlobalOrientation( Math::MatrixToMat33( value ) );
}
Matrix FluidEmitter::LocalPose::get()
{
	return Math::Mat34ToMatrix( &_fluidEmitter->getLocalPose() );
}
void FluidEmitter::LocalPose::set( Matrix value )
{
	_fluidEmitter->setLocalPose( Math::MatrixToMat34( value ) );
}
Vector3 FluidEmitter::LocalPosition::get()
{
	return Math::NxVec3ToVector3( _fluidEmitter->getLocalPosition() );
}
void FluidEmitter::LocalPosition::set( Vector3 value )
{
	_fluidEmitter->setLocalPosition( Math::Vector3ToNxVec3( value ) );
}
Matrix FluidEmitter::LocalOrientation::get()
{
	return Math::Mat33ToMatrix( &_fluidEmitter->getLocalOrientation() );
}
void FluidEmitter::LocalOrientation::set( Matrix value )
{
	_fluidEmitter->setLocalOrientation( Math::MatrixToMat33( value ) );
}

Shape^ FluidEmitter::FrameShape::get()
{
	return _shape;
}
void FluidEmitter::FrameShape::set( Shape^ value )
{
	_shape = value;
	
	if( value == nullptr )
		_fluidEmitter->setFrameShape( NULL );
	else
		_fluidEmitter->setFrameShape( value->UnmanagedPointer );
}

int FluidEmitter::MaximumParticles::get()
{
	return _fluidEmitter->getMaxParticles();
}

float FluidEmitter::DimensionX::get()
{
	return _fluidEmitter->getDimensionX();
}
float FluidEmitter::DimensionY::get()
{
	return _fluidEmitter->getDimensionY();
}

Vector3 FluidEmitter::RandomPosition::get()
{
	return Math::NxVec3ToVector3( _fluidEmitter->getRandomPos() );
}
void FluidEmitter::RandomPosition::set( Vector3 value )
{
	_fluidEmitter->setRandomPos( Math::Vector3ToNxVec3( value ) );
}

float FluidEmitter::RandomAngle::get()
{
	return _fluidEmitter->getRandomAngle();
}
void FluidEmitter::RandomAngle::set( float value )
{
	_fluidEmitter->setRandomAngle( value );
}

float FluidEmitter::FluidVelocityMagnitude::get()
{
	return _fluidEmitter->getFluidVelocityMagnitude();
}
void FluidEmitter::FluidVelocityMagnitude::set( float value )
{
	_fluidEmitter->setFluidVelocityMagnitude( value );
}

float FluidEmitter::Rate::get()
{
	return _fluidEmitter->getRate();
}
void FluidEmitter::Rate::set( float value )
{
	_fluidEmitter->setRate( value );
}

float FluidEmitter::ParticleLifetime::get()
{
	return _fluidEmitter->getParticleLifetime();
}
void FluidEmitter::ParticleLifetime::set( float value )
{
	_fluidEmitter->setParticleLifetime( value );
}

float FluidEmitter::RepulsionCoefficient::get()
{
	return _fluidEmitter->getRepulsionCoefficient();
}
void FluidEmitter::RepulsionCoefficient::set( float value )
{
	_fluidEmitter->setRepulsionCoefficient( value );
}

Object^ FluidEmitter::UserData::get()
{
	return _userData;
}
void FluidEmitter::UserData::set( Object^ value )
{
	_userData = value;
}

NxFluidEmitter* FluidEmitter::UnmanagedPointer::get()
{
	return _fluidEmitter;
}