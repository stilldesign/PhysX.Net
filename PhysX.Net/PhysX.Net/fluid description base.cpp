#include "StdAfx.h"

#include "Fluid Description Base.h"
#include "Functions.h"
#include "Groups Mask.h"
#include "Particle Data.h"
#include "Physics Stream.h"
#include "Descriptor Validity.h"
#include "Compartment.h"
#include "Particle Id Data.h"
#include "Fluid Packet Data.h"

#include <NxFluidDesc.h>

using namespace StillDesign::PhysX;

FluidDescriptionBase::FluidDescriptionBase( NxFluidDescBase* fluidDescription )
{
	Debug::Assert( fluidDescription != NULL );
	
	_fluidDescBase = fluidDescription;
	
	_initialParticleData = gcnew ParticleData();
	_particleWriteData = gcnew ParticleData();
	_particleDeletionWriteData = gcnew ParticleIdData();
	_particleCreationWriteData = gcnew ParticleIdData();
	_fluidPacketData = gcnew StillDesign::PhysX::FluidPacketData();
}
FluidDescriptionBase::~FluidDescriptionBase()
{
	this->!FluidDescriptionBase();
}
FluidDescriptionBase::!FluidDescriptionBase()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	SAFE_DELETE( _fluidDescBase );
	
	_initialParticleData = nullptr;
	_particleWriteData = nullptr;
	
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool FluidDescriptionBase::IsDisposed::get()
{
	return (_fluidDescBase == NULL);
}

void FluidDescriptionBase::SetToDefault()
{
	_fluidDescBase->setToDefault();
	
	_initialParticleData->SetToDefault();
	_particleWriteData->SetToDefault();
	_particleDeletionWriteData->SetToDefault();
	_particleCreationWriteData->SetToDefault();
	_fluidPacketData->SetToDefault();
	
	_compartment = nullptr;
				
}
DescriptorValidity^ FluidDescriptionBase::IsValid()
{
	if( _fluidDescBase->kernelRadiusMultiplier < 1.0f )
		return gcnew DescriptorValidity( false, -1, "kernelRadiusMultiplier < 1.0f" );
	
	if( _fluidDescBase->restDensity <= 0.0f )
		return gcnew DescriptorValidity( false, -2, "restDensity <= 0.0f" );
	
	if( _fluidDescBase->restParticlesPerMeter <= 0.0f )
		return gcnew DescriptorValidity( false, -3, "restParticlesPerMeter <= 0.0f" );

	if (_fluidDescBase->packetSizeMultiplier < 4)
		return gcnew DescriptorValidity( false, -4, "packetSizeMultiplier < 4" );
	if (_fluidDescBase->packetSizeMultiplier & ( _fluidDescBase->packetSizeMultiplier - 1 ) )
		return gcnew DescriptorValidity( false, -5, "packetSizeMultiplier & ( packetSizeMultiplier - 1 )" );

	if (_fluidDescBase->motionLimitMultiplier <= 0.0f)
		return gcnew DescriptorValidity( false, -6, "motionLimitMultiplier <= 0.0f" );
	if (_fluidDescBase->motionLimitMultiplier > _fluidDescBase->packetSizeMultiplier*_fluidDescBase->kernelRadiusMultiplier)
		return gcnew DescriptorValidity( false, -7, "motionLimitMultiplier > packetSizeMultiplier*kernelRadiusMultiplier" );

	if (_fluidDescBase->collisionDistanceMultiplier <= 0.0f)
		return gcnew DescriptorValidity( false, -8, "collisionDistanceMultiplier <= 0.0f" );
	if (_fluidDescBase->collisionDistanceMultiplier > _fluidDescBase->packetSizeMultiplier*_fluidDescBase->kernelRadiusMultiplier)
		return gcnew DescriptorValidity( false, -9, "collisionDistanceMultiplier > packetSizeMultiplier*kernelRadiusMultiplier" );

	if (_fluidDescBase->stiffness <= 0.0f)
		return gcnew DescriptorValidity( false, -10, "stiffness <= 0.0f" );
	if (_fluidDescBase->viscosity <= 0.0f)
		return gcnew DescriptorValidity( false, -11, "viscosity <= 0.0f" );

	bool isNoInteraction = (_fluidDescBase->simulationMethod & NX_F_NO_PARTICLE_INTERACTION) > 0;
	bool isSPH = (_fluidDescBase->simulationMethod & NX_F_SPH) > 0;
	bool isMixed = (_fluidDescBase->simulationMethod & NX_F_MIXED_MODE) > 0;
	if (!(isNoInteraction || isSPH || isMixed))
		return gcnew DescriptorValidity( false, -12, "!(isNoInteraction || isSPH || isMixed)" );
	if (isNoInteraction && (isSPH || isMixed))
		return gcnew DescriptorValidity( false, -13, "isNoInteraction && (isSPH || isMixed)" );
	if (isSPH && (isNoInteraction || isMixed))
		return gcnew DescriptorValidity( false, -14, "isSPH && (isNoInteraction || isMixed)" );
	if (isMixed && (isNoInteraction || isSPH))
		return gcnew DescriptorValidity( false, -15, "isMixed && (isNoInteraction || isSPH)" );
	
	if (_fluidDescBase->damping < 0.0f)
		return gcnew DescriptorValidity( false, -16, "damping < 0.0f" );
	if (_fluidDescBase->fadeInTime < 0.0f)
		return gcnew DescriptorValidity( false, -17, "fadeInTime < 0.0f" );

	if (_fluidDescBase->dynamicFrictionForDynamicShapes < 0.0f || _fluidDescBase->dynamicFrictionForDynamicShapes > 1.0f)
		return gcnew DescriptorValidity( false, -18, "DynamicFrictionForDynamicShapes < 0.0f || DynamicFrictionForDynamicShapes > 1.0f" );
	if (_fluidDescBase->restitutionForDynamicShapes < 0.0f || _fluidDescBase->restitutionForDynamicShapes > 1.0f)
		return gcnew DescriptorValidity( false, -19, "RestitutionForDynamicShapes < 0.0f || RestitutionForDynamicShapes > 1.0f" );
	if (_fluidDescBase->attractionForDynamicShapes < 0.0f)
		return gcnew DescriptorValidity( false, -20, "AttractionForDynamicShapes < 0.0f" );
	if (_fluidDescBase->dynamicFrictionForStaticShapes < 0.0f || _fluidDescBase->dynamicFrictionForStaticShapes > 1.0f)
		return gcnew DescriptorValidity( false, -21, "DynamicFrictionForStaticShapes < 0.0f || DynamicFrictionForStaticShapes > 1.0f" );
	if (_fluidDescBase->restitutionForStaticShapes < 0.0f || _fluidDescBase->restitutionForStaticShapes > 1.0f)
		return gcnew DescriptorValidity( false, -22, "RestitutionForStaticShapes < 0.0f || RestitutionForStaticShapes > 1.0f" );
	if (_fluidDescBase->attractionForStaticShapes < 0.0f)
		return gcnew DescriptorValidity( false, -23, "AttractionForStaticShapes < 0.0f" );
	if (_fluidDescBase->collisionResponseCoefficient < 0.0f)
		return gcnew DescriptorValidity( false, -24, "collisionResponseCoefficient < 0.0f" );
	
	if (!_fluidDescBase->initialParticleData.isValid())
		return gcnew DescriptorValidity( false, -25, "!initialParticleData.isValid()" );
	if (!_fluidDescBase->particlesWriteData.isValid())
		return gcnew DescriptorValidity( false, -26, "!particlesWriteData.isValid()" );
	if (!_fluidDescBase->particleDeletionIdWriteData.isValid())
		return gcnew DescriptorValidity( false, -27, "!particleDeletionIdWriteData.isValid()" );
	if (!_fluidDescBase->particleCreationIdWriteData.isValid())
		return gcnew DescriptorValidity( false, -28, "!particleCreationIdWriteData.isValid()" );
	if (!_fluidDescBase->fluidPacketData.isValid())
		return gcnew DescriptorValidity( false, -29, "!fluidPacketData.isValid()" );
	
	if (_fluidDescBase->maxParticles > 32767)
		return gcnew DescriptorValidity( false, -30, "maxParticles > 32767" );
	if (_fluidDescBase->maxParticles < 1)
		return gcnew DescriptorValidity( false, -31, "maxParticles < 1" );
	
	if (_fluidDescBase->numReserveParticles >= _fluidDescBase->maxParticles)
		return gcnew DescriptorValidity( false, -32, "numReserveParticles >= maxParticles" );
	
	if(_fluidDescBase->collisionGroup >= 32)
		return gcnew DescriptorValidity( false, -33, "collisionGroup >= 32" ); // We only support 32 different collision groups
	
	return true;
}

ParticleData^ FluidDescriptionBase::InitialParticleData::get()
{
	return _initialParticleData;
}
//void FluidDescriptionBase::InitialParticleData::set( ParticleData^ value )
//{
//	if( value != nullptr && value->IsDisposed == true )
//		throw gcnew ArgumentException( "Initial particle data cannot disposed" );
//	
//	_initialParticleData = value;
//	
//	if( value == nullptr )
//		_fluidDescBase->initialParticleData = NULL;
//	else
//		_fluidDescBase->initialParticleData = *value->UnmanagedPointer;
//}
ParticleData^ FluidDescriptionBase::ParticleWriteData::get()
{
	return _particleWriteData;
}
//void FluidDescriptionBase::SetParticleWriteData( ParticleData^ value )
//{
//	if( value != nullptr && value->IsDisposed == true )
//		throw gcnew ArgumentException( "Particle write data cannot disposed" );
//	
//	_particleWriteData = value;
//	
//	if( value == nullptr )
//		_fluidDescBase->particlesWriteData = NULL;
//	else
//		_fluidDescBase->particlesWriteData = *value->UnmanagedPointer;
//}

ParticleIdData^ FluidDescriptionBase::ParticleDeletionIdWriteData::get()
{
	return _particleDeletionWriteData;
}
//void FluidDescriptionBase::ParticleDeletionIdWriteData::set( ParticleData^ value )
//{
//	if( value != nullptr && value->IsDisposed == true )
//		throw gcnew ArgumentException( "Particle Deletion Id Write Data cannot disposed" );
//	
//	_particleDeletionWriteData = value;
//	
//	if( value == nullptr )
//		_fluidDescBase->particleDeletionWriteData = NULL;
//	else
//		_fluidDescBase->particleDeletionWriteData = *value->UnmanagedPointer;
//}

ParticleIdData^ FluidDescriptionBase::ParticleCreationIdWriteData::get()
{
	return _particleCreationWriteData;
}
//void FluidDescriptionBase::ParticleCreationIdWriteData::set( ParticleData^ value )
//{
//	if( value != nullptr && value->IsDisposed == true )
//		throw gcnew ArgumentException( "Particle Creation Id Write Data cannot disposed" );
//	
//	_particleCreationWriteData = value;
//	
//	if( value == nullptr )
//		_fluidDescBase->particleCreationWriteData = NULL;
//	else
//		_fluidDescBase->particleCreationWriteData = *value->UnmanagedPointer;
//}

StillDesign::PhysX::FluidPacketData^ FluidDescriptionBase::FluidPacketData::get()
{
	return _fluidPacketData;
}
//void FluidDescriptionBase::FluidPacketData::set( StillDesign::PhysX::FluidPacketData^ value )
//{
//	if( value != nullptr && value->IsDisposed == true )
//		throw gcnew ArgumentException( "Fluid Packet Data cannot disposed" );
//	
//	_fluidPacketData = value;
//	
//	if( value == nullptr )
//		_fluidDescBase->fluidPacketData = NULL;
//	else
//		_fluidDescBase->fluidPacketData = *value->UnmanagedPointer;
//}

StillDesign::PhysX::Compartment^ FluidDescriptionBase::Compartment::get()
{
	return _compartment;
}
void FluidDescriptionBase::Compartment::set( StillDesign::PhysX::Compartment^ value )
{
	_compartment = value;
	
	if( value != nullptr )
		_fluidDescBase->compartment = value->UnmanagedPointer;
	else
		_fluidDescBase->compartment = NULL;
}

String^ FluidDescriptionBase::Name::get()
{
	return Functions::UnmanagedToManagedString( _fluidDescBase->name );
}
void FluidDescriptionBase::Name::set( String^ value )
{
	_fluidDescBase->name = Functions::ManagedToUnmanagedString( value );
}

FluidDescriptionType FluidDescriptionBase::Type::get()
{
	return (FluidDescriptionType)_fluidDescBase->getType();
}

int FluidDescriptionBase::MaximumParticles::get()
{
	return _fluidDescBase->maxParticles;
}
void FluidDescriptionBase::MaximumParticles::set( int value )
{
	_fluidDescBase->maxParticles = value;
}

int FluidDescriptionBase::NumberOfReservedParticles::get()
{
	return _fluidDescBase->numReserveParticles;
}
void FluidDescriptionBase::NumberOfReservedParticles::set( int value )
{
	_fluidDescBase->numReserveParticles = value;
}

float FluidDescriptionBase::RestParticlesPerMeter::get()
{
	return _fluidDescBase->restParticlesPerMeter;
}
void FluidDescriptionBase::RestParticlesPerMeter::set( float value )
{
	_fluidDescBase->restParticlesPerMeter = value;
}

float FluidDescriptionBase::RestDensity::get()
{
	return _fluidDescBase->restDensity;
}
void FluidDescriptionBase::RestDensity::set( float value )
{
	_fluidDescBase->restDensity = value;
}

float FluidDescriptionBase::KernelRadiusMultiplier::get()
{
	return _fluidDescBase->kernelRadiusMultiplier;
}
void FluidDescriptionBase::KernelRadiusMultiplier::set( float value )
{
	_fluidDescBase->kernelRadiusMultiplier = value;
}

float FluidDescriptionBase::MotionLimitMultiplier::get()
{
	return _fluidDescBase->motionLimitMultiplier;
}
void FluidDescriptionBase::MotionLimitMultiplier::set( float value )
{
	_fluidDescBase->motionLimitMultiplier = value;
}

float FluidDescriptionBase::CollisionDistanceMultiplier::get()
{
	return _fluidDescBase->collisionDistanceMultiplier;
}
void FluidDescriptionBase::CollisionDistanceMultiplier::set( float value )
{
	_fluidDescBase->collisionDistanceMultiplier = value;
}

int FluidDescriptionBase::PacketSizeMultiplier::get()
{
	return _fluidDescBase->packetSizeMultiplier;
}
void FluidDescriptionBase::PacketSizeMultiplier::set( int value )
{
	_fluidDescBase->packetSizeMultiplier = value;
}

float FluidDescriptionBase::Stiffness::get()
{
	return _fluidDescBase->stiffness;
}
void FluidDescriptionBase::Stiffness::set( float value )
{
	_fluidDescBase->stiffness = value;
}

float FluidDescriptionBase::Viscosity::get()
{
	return _fluidDescBase->viscosity;
}
void FluidDescriptionBase::Viscosity::set( float value )
{
	_fluidDescBase->viscosity = value;
}

float FluidDescriptionBase::SurfaceTension::get()
{
	return _fluidDescBase->surfaceTension;
}
void FluidDescriptionBase::SurfaceTension::set( float value )
{
	_fluidDescBase->surfaceTension = value;
}

float FluidDescriptionBase::Damping::get()
{
	return _fluidDescBase->damping;
}
void FluidDescriptionBase::Damping::set( float value )
{
	_fluidDescBase->damping = value;
}

float FluidDescriptionBase::FadeInTime::get()
{
	return _fluidDescBase->fadeInTime;
}
void FluidDescriptionBase::FadeInTime::set( float value )
{
	_fluidDescBase->fadeInTime = value;
}

Vector3 FluidDescriptionBase::ExternalAcceleration::get()
{
	return Math::NxVec3ToVector3( _fluidDescBase->externalAcceleration );
}
void FluidDescriptionBase::ExternalAcceleration::set( Vector3 value )
{
	_fluidDescBase->externalAcceleration = Math::Vector3ToNxVec3( value );
}

Plane FluidDescriptionBase::ProjectionPlane::get()
{
	return Math::NxPlaneToPlane( _fluidDescBase->projectionPlane );
}
void FluidDescriptionBase::ProjectionPlane::set( Plane value )
{
	_fluidDescBase->projectionPlane = Math::PlaneToNxPlane( value );
}

float FluidDescriptionBase::RestitutionForStaticShapes::get()
{
	return _fluidDescBase->restitutionForStaticShapes;
}
void FluidDescriptionBase::RestitutionForStaticShapes::set( float value )
{
	_fluidDescBase->restitutionForStaticShapes = value;
}

float FluidDescriptionBase::DynamicFrictionForStaticShapes::get()
{
	return _fluidDescBase->dynamicFrictionForStaticShapes;
}
void FluidDescriptionBase::DynamicFrictionForStaticShapes::set( float value )
{
	_fluidDescBase->dynamicFrictionForStaticShapes = value;
}

float FluidDescriptionBase::StaticFrictionForStaticShapes::get()
{
	return _fluidDescBase->staticFrictionForStaticShapes;
}
void FluidDescriptionBase::StaticFrictionForStaticShapes::set( float value )
{
	_fluidDescBase->staticFrictionForStaticShapes = value;
}

float FluidDescriptionBase::AttractionForStaticShapes::get()
{
	return _fluidDescBase->attractionForStaticShapes;
}
void FluidDescriptionBase::AttractionForStaticShapes::set( float value )
{
	_fluidDescBase->attractionForStaticShapes = value;
}

float FluidDescriptionBase::RestitutionForDynamicShapes::get()
{
	return _fluidDescBase->restitutionForDynamicShapes;
}
void FluidDescriptionBase::RestitutionForDynamicShapes::set( float value )
{
	_fluidDescBase->restitutionForDynamicShapes = value;
}

float FluidDescriptionBase::DynamicFrictionForDynamicShapes::get()
{
	return _fluidDescBase->dynamicFrictionForDynamicShapes;
}
void FluidDescriptionBase::DynamicFrictionForDynamicShapes::set( float value )
{
	_fluidDescBase->dynamicFrictionForDynamicShapes = value;
}

float FluidDescriptionBase::StaticFrictionForDynamicShapes::get()
{
	return _fluidDescBase->staticFrictionForDynamicShapes;
}
void FluidDescriptionBase::StaticFrictionForDynamicShapes::set( float value )
{
	_fluidDescBase->staticFrictionForDynamicShapes = value;
}

float FluidDescriptionBase::AttractionForDynamicShapes::get()
{
	return _fluidDescBase->attractionForDynamicShapes;
}
void FluidDescriptionBase::AttractionForDynamicShapes::set( float value )
{
	_fluidDescBase->attractionForDynamicShapes = value;
}

float FluidDescriptionBase::CollisionResponseCoefficient::get()
{
	return _fluidDescBase->collisionResponseCoefficient;
}
void FluidDescriptionBase::CollisionResponseCoefficient::set( float value )
{
	_fluidDescBase->collisionResponseCoefficient = value;
}

FluidSimulationMethod FluidDescriptionBase::SimulationMethod::get()
{
	return (FluidSimulationMethod)_fluidDescBase->simulationMethod;
}
void FluidDescriptionBase::SimulationMethod::set( FluidSimulationMethod value )
{
	_fluidDescBase->simulationMethod = (NxFluidSimulationMethod)value;
}

FluidCollisionMethod FluidDescriptionBase::CollisionMethod::get()
{
	return (FluidCollisionMethod)_fluidDescBase->collisionMethod;
}
void FluidDescriptionBase::CollisionMethod::set( FluidCollisionMethod value )
{
	_fluidDescBase->collisionMethod = (NxFluidCollisionMethod)value;
}

short FluidDescriptionBase::CollisionGroup::get()
{
	return _fluidDescBase->collisionGroup;
}
void FluidDescriptionBase::CollisionGroup::set( short value )
{
	_fluidDescBase->collisionGroup = value;
}

StillDesign::PhysX::GroupsMask FluidDescriptionBase::GroupsMask::get()
{
	return (StillDesign::PhysX::GroupsMask)_fluidDescBase->groupsMask;
}
void FluidDescriptionBase::GroupsMask::set( StillDesign::PhysX::GroupsMask value )
{
	_fluidDescBase->groupsMask = (NxGroupsMask)value;
}

short FluidDescriptionBase::ForceFieldMaterial::get()
{
	return _fluidDescBase->forceFieldMaterial;
}
void FluidDescriptionBase::ForceFieldMaterial::set( short value )
{
	_fluidDescBase->forceFieldMaterial = value;
}

FluidFlag FluidDescriptionBase::Flags::get()
{
	return (FluidFlag)_fluidDescBase->flags;
}
void FluidDescriptionBase::Flags::set( FluidFlag value )
{
	_fluidDescBase->flags = (NxFluidFlag)value;
}

Object^ FluidDescriptionBase::UserData::get()
{
	return _userData;
}
void FluidDescriptionBase::UserData::set( Object^ value )
{
	_userData = value;
}

NxFluidDescBase* FluidDescriptionBase::UnmanagedPointer::get()
{
	return _fluidDescBase;
}