#include "StdAfx.h"

#include "Fluid.h"
#include "Fluid Description.h"
#include "Functions.h"
#include "Scene.h"
//#include "Implicit Screen Mesh.h"
//#include "Implicit Screen Mesh Description.h"
#include "Fluid Emitter.h"
#include "Fluid Emitter Description.h"
#include "Particle Update Data.h"
#include "Particle Id Data.h"
#include "Fluid Packet Data.h"
#include "Particle Data.h"

using namespace StillDesign::PhysX;

Fluid::Fluid( NxFluid* fluid )
{
	Debug::Assert( fluid != NULL );
	
	ObjectCache::Add( (intptr_t)fluid, this );
	
	_fluid = fluid;
	_scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&fluid->getScene()) );
	
	if( fluid->getCompartment() != NULL )
		_compartment = ObjectCache::GetObject<StillDesign::PhysX::Compartment^>( (intptr_t)fluid->getCompartment() );
	
	_particleWriteData = gcnew StillDesign::PhysX::ParticleData( fluid->getParticlesWriteData() );
	_particleCreationIdWriteData = gcnew StillDesign::PhysX::ParticleIdData( fluid->getParticleCreationIdWriteData() );
	_particleDeletionIdWriteData = gcnew StillDesign::PhysX::ParticleIdData( fluid->getParticleDeletionIdWriteData() );
	_fluidPacketData = gcnew StillDesign::PhysX::FluidPacketData( fluid->getFluidPacketData() );
	
	_fluidEmitters = gcnew ElementCollection< FluidEmitter^, FluidEmitterCollection^ >();
	for( unsigned int x = 0; x < fluid->getNbEmitters(); x++ )
	{
		NxFluidEmitter* emitter = fluid->getEmitters()[ x ];
		if( emitter == NULL )
			continue;
		
		_fluidEmitters->Add( gcnew FluidEmitter( emitter ) );
	}
}
Fluid::Fluid( NxFluid* fluid, ParticleData^ particleWriteData, ParticleIdData^ particleDeletionIdWriteData, ParticleIdData^ particleCreationIdWriteData, StillDesign::PhysX::FluidPacketData^ fluidPacketData )
{
	Debug::Assert( fluid != NULL );
	
	ObjectCache::Add( (intptr_t)fluid, this );
	
	_fluid = fluid;
	_scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&fluid->getScene()) );
	
	if( fluid->getCompartment() != NULL )
		_compartment = ObjectCache::GetObject<StillDesign::PhysX::Compartment^>( (intptr_t)fluid->getCompartment() );
	
	_particleWriteData = particleWriteData;
	_particleDeletionIdWriteData = particleDeletionIdWriteData;
	_particleCreationIdWriteData = particleCreationIdWriteData;
	_fluidPacketData = fluidPacketData;
	
	_fluidEmitters = gcnew ElementCollection< FluidEmitter^, FluidEmitterCollection^ >();
	for( unsigned int x = 0; x < fluid->getNbEmitters(); x++ )
	{
		NxFluidEmitter* emitter = fluid->getEmitters()[ x ];
		if( emitter == NULL )
			continue;
		
		_fluidEmitters->Add( gcnew FluidEmitter( emitter ) );
	}
}
Fluid::~Fluid()
{
	this->!Fluid();
}
Fluid::!Fluid()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	_fluidEmitters->DiposeOfAll();
	
	_scene->UnmanagedPointer->releaseFluid( *_fluid );
	
	_fluid = NULL;
	
	_scene = nullptr;
	_particleWriteData = nullptr;
	_userData = nullptr;
	
	_fluidEmitters = nullptr;
	//_implicitScreenMesh = nullptr;
	
	onDisposed( this, nullptr );
}

bool Fluid::IsDisposed::get()
{
	return ( _fluid == NULL );
}

FluidDescription^ Fluid::SaveToDescription()
{
	return SaveToDescription( true );
}
FluidDescription^ Fluid::SaveToDescription( bool saveEmitters )
{
	NxFluidDesc* desc = new NxFluidDesc();
	
	if( _fluid->saveToDesc( *desc ) == false )
	{
		delete desc;
		return nullptr;
	}
	
	if( saveEmitters == true )
		_fluid->saveEmittersToFluidDesc( *desc );
	
	FluidDescription^ d = gcnew FluidDescription( desc );
		// These stream should be created by the fluid description base's constructor to wrap the passed in data
		//d->ParticleWriteData = this->ParticleWriteData;
		//d->ParticleDeletionIdWriteData = this->ParticleDeletionIdWriteData;
		//d->ParticleCreationIdWriteData = this->ParticleCreationIdWriteData;
		//d->FluidPacketData = this->FluidPacketData;
		d->Compartment = this->Compartment;
		d->UserData = this->UserData;
	
	return d;
}
void Fluid::LoadFromDescription( FluidDescription^ description )
{
	ThrowIfNull( description, "description" );
	
	_fluid->loadFromDesc( *description->UnmanagedPointer );
}

FluidEmitter^ Fluid::CreateFluidEmitter( FluidEmitterDescription^ description )
{
	ThrowIfNull( description, "description" );
	
	if( description->IsValid() == false )
		throw gcnew ArgumentException( "Description is invalid" );
	
	NxFluidEmitter* emitter = _fluid->createEmitter( *description->UnmanagedPointer );
	if( emitter == NULL )
		throw gcnew Exception( "Failed to create emitter" );
	
	FluidEmitter^ e = gcnew FluidEmitter( emitter );
	
	_fluidEmitters->Add( e );
	
	return e;
}
//ImplicitScreenMesh^ Fluid::CreateImplicitScreenMesh( ImplicitScreenMeshDescription^ description )
//{
//	if( description->IsValid() == false )
//		throw gcnew ArgumentException( "Implicit screen mesh description is invalid", "description" );
//	
//	NxImplicitScreenMesh* implicitScreenMesh = _fluid->createScreenSurfaceMesh( *description->UnmanagedPointer );
//	
//	ImplicitScreenMesh^ ism = ImplicitScreenMesh::FromUnmanagedPointer( implicitScreenMesh, this );
//		ism->MeshData = description->MeshData;
//	
//	_implicitScreenMesh->Add( ism );
//	
//	return ism;
//}

bool Fluid::GetFlag( FluidFlag flag )
{
	return _fluid->getFlag( (NxFluidFlag)flag );
}
void Fluid::SetFlag( FluidFlag flag, bool value )
{
	_fluid->setFlag( (NxFluidFlag)flag, value );
}

Bounds3 Fluid::GetWorldBounds()
{
	NxBounds3 b;
	_fluid->getWorldBounds( b );
	
	return (Bounds3)b;
}

void Fluid::AddParticles( ParticleData^ particleData )
{
	AddParticles( particleData, false );
}
void Fluid::AddParticles( ParticleData^ particleData, bool appendIds )
{
	ThrowIfNullOrDisposed( particleData, "particleData" );
	
	_fluid->addParticles( *particleData->UnmanagedPointer, appendIds );
}
void Fluid::RemoveAllParticles()
{
	_fluid->removeAllParticles();
}
void Fluid::UpdateParticles( ParticleUpdateData^ updateData )
{
	ThrowIfNullOrDisposed( updateData, "updateData" );
	
	_fluid->updateParticles( *updateData->UnmanagedPointer );
}

Fluid::FluidEmitterCollection^ Fluid::Emitters::get()
{
	return _fluidEmitters->ReadOnlyCollection;
}

//Fluid::ImplicitScreenMeshCollection^ Fluid::ImplicitScreenMeshes::get()
//{
//	return _implicitScreenMesh->ReadOnlyCollection;
//}

String^ Fluid::Name::get()
{
	return ToManagedString( _fluid->getName() );
}
void Fluid::Name::set( String^ value )
{
	_fluid->setName( ToUnmanagedString( value ) );
}

StillDesign::PhysX::Scene^ Fluid::Scene::get()
{
	return _scene;
}

StillDesign::PhysX::Compartment^ Fluid::Compartment::get()
{
	return _compartment;
}

int Fluid::MaximumParticles::get()
{
	return _fluid->getMaxParticles();
}

int Fluid::NumberOfReservedParticles::get()
{
	return _fluid->getNumReserveParticles();
}
void Fluid::NumberOfReservedParticles::set( int value )
{
	_fluid->setNumReserveParticles( value );
}

int Fluid::CurrentParticleLimit::get()
{
	return _fluid->getCurrentParticleLimit();
}
void Fluid::CurrentParticleLimit::set( int value )
{
	_fluid->setCurrentParticleLimit( value );
}

float Fluid::RestParticlesPerMeter::get()
{
	return _fluid->getRestParticlesPerMeter();
}

float Fluid::RestDensity::get()
{
	return _fluid->getRestDensity();
}

float Fluid::KernelRadiusMultiplier::get()
{
	return _fluid->getKernelRadiusMultiplier();
}

float Fluid::MotionLimitMultiplier::get()
{
	return _fluid->getMotionLimitMultiplier();
}

float Fluid::CollisionDistanceMultiplier::get()
{
	return _fluid->getCollisionDistanceMultiplier();
}

int Fluid::PacketSizeMultiplier::get()
{
	return _fluid->getPacketSizeMultiplier();
}

float Fluid::Stiffness::get()
{
	return _fluid->getStiffness();
}
void Fluid::Stiffness::set( float value )
{
	_fluid->setStiffness( value );
}

float Fluid::Viscosity::get()
{
	return _fluid->getViscosity();
}
void Fluid::Viscosity::set( float value )
{
	_fluid->setViscosity( value );
}

float Fluid::SurfaceTension::get()
{
	return _fluid->getSurfaceTension();
}
void Fluid::SurfaceTension::set( float value )
{
	_fluid->setSurfaceTension( value );
}

float Fluid::Damping::get()
{
	return _fluid->getDamping();
}
void Fluid::Damping::set( float value )
{
	_fluid->setDamping( value );
}

float Fluid::FadeInTime::get()
{
	return _fluid->getFadeInTime();
}
void Fluid::FadeInTime::set( float value )
{
	_fluid->setFadeInTime( value );
}

Vector3 Fluid::ExternalAcceleration::get()
{
	return Math::NxVec3ToVector3( _fluid->getExternalAcceleration() );
}
void Fluid::ExternalAcceleration::set( Vector3 value )
{
	_fluid->setExternalAcceleration( Math::Vector3ToNxVec3( value ) );
}

Plane Fluid::ProjectionPlane::get()
{
	return Math::NxPlaneToPlane( _fluid->getProjectionPlane() );
}
void Fluid::ProjectionPlane::set( Plane value )
{
	_fluid->setProjectionPlane( Math::PlaneToNxPlane( value ) );
}

float Fluid::RestitutionForStaticShapes::get()
{
	return _fluid->getRestitutionForStaticShapes();
}
void Fluid::RestitutionForStaticShapes::set( float value )
{
	_fluid->setRestitutionForStaticShapes( value );
}

float Fluid::DynamicFrictionForStaticShapes::get()
{
	return _fluid->getDynamicFrictionForStaticShapes();
}
void Fluid::DynamicFrictionForStaticShapes::set( float value )
{
	_fluid->setDynamicFrictionForStaticShapes( value );
}

float Fluid::StaticFrictionForStaticShapes::get()
{
	return _fluid->getStaticFrictionForStaticShapes();
}
void Fluid::StaticFrictionForStaticShapes::set( float value )
{
	_fluid->setStaticFrictionForStaticShapes( value );
}

float Fluid::StaticFrictionForDynamicShapes::get()
{
	return _fluid->getStaticFrictionForDynamicShapes();
}
void Fluid::StaticFrictionForDynamicShapes::set( float value )
{
	_fluid->setStaticFrictionForDynamicShapes( value );
}

float Fluid::AttractionForStaticShapes::get()
{
	return _fluid->getAttractionForStaticShapes();
}
void Fluid::AttractionForStaticShapes::set( float value )
{
	_fluid->setAttractionForStaticShapes( value );
}

float Fluid::RestitutionForDynamicShapes::get()
{
	return _fluid->getRestitutionForDynamicShapes();
}
void Fluid::RestitutionForDynamicShapes::set( float value )
{
	_fluid->setRestitutionForDynamicShapes( value );
}

float Fluid::DynamicFrictionForDynamicShapes::get()
{
	return _fluid->getDynamicFrictionForDynamicShapes();
}
void Fluid::DynamicFrictionForDynamicShapes::set( float value )
{
	_fluid->setDynamicFrictionForDynamicShapes( value );
}

float Fluid::AttractionForDynamicShapes::get()
{
	return _fluid->getAttractionForDynamicShapes();
}
void Fluid::AttractionForDynamicShapes::set( float value )
{
	_fluid->setAttractionForDynamicShapes( value );
}

float Fluid::CollisionResponseCoefficient::get()
{
	return _fluid->getCollisionResponseCoefficient();
}
void Fluid::CollisionResponseCoefficient::set( float value )
{
	_fluid->setCollisionResponseCoefficient( value );
}

FluidSimulationMethod Fluid::SimulationMethod::get()
{
	return (FluidSimulationMethod)_fluid->getSimulationMethod();
}
void Fluid::SimulationMethod::set( FluidSimulationMethod value )
{
	_fluid->setSimulationMethod( (NxFluidSimulationMethod)value );
}

FluidCollisionMethod Fluid::CollisionMethod::get()
{
	return (FluidCollisionMethod)_fluid->getCollisionMethod();
}
void Fluid::CollisionMethod::set( FluidCollisionMethod value )
{
	_fluid->setCollisionMethod( (NxFluidCollisionMethod)value );
}

short Fluid::CollisionGroup::get()
{
	return _fluid->getGroup();
}
void Fluid::CollisionGroup::set( short value )
{
	_fluid->setGroup( value );
}

 ParticleData^ Fluid::ParticleWriteData::get()
{
	return _particleWriteData;
}
void Fluid::ParticleWriteData::set( ParticleData^ value )
{
	ThrowIfNull( value, "value" );
	
	_particleWriteData = value;
	
	_fluid->setParticlesWriteData( *value->UnmanagedPointer );
}
ParticleIdData^ Fluid::ParticleDeletionIdWriteData::get()
{
	return _particleDeletionIdWriteData;
}
void Fluid::ParticleDeletionIdWriteData::set( ParticleIdData^ value )
{
	ThrowIfNull( value, "value" );
	
	_particleDeletionIdWriteData = value;
	
	_fluid->setParticleDeletionIdWriteData( *value->UnmanagedPointer );
}
ParticleIdData^ Fluid::ParticleCreationIdWriteData::get()
{
	return _particleCreationIdWriteData;
}
void Fluid::ParticleCreationIdWriteData::set( ParticleIdData^ value )
{
	ThrowIfNull( value, "value" );
	
	_particleCreationIdWriteData = value;
	
	_fluid->setParticleCreationIdWriteData( *value->UnmanagedPointer );
}
StillDesign::PhysX::FluidPacketData^ Fluid::FluidPacketData::get()
{
	return _fluidPacketData;
}
void Fluid::FluidPacketData::set( StillDesign::PhysX::FluidPacketData^ value )
{
	ThrowIfNull( value, "value" );
	
	_fluidPacketData = value;
	
	_fluid->setFluidPacketData( *value->UnmanagedPointer );
}

Object^ Fluid::UserData::get()
{
	return _userData;
}
void Fluid::UserData::set( Object^ value )
{
	_userData = value;
}

NxFluid* Fluid::UnmanagedPointer::get()
{
	return _fluid;
}