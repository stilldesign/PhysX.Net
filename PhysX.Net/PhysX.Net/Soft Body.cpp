#include "StdAfx.h"

#include "Soft Body.h"
#include "Soft Body Description.h"
#include "Mesh Data.h"
#include "Groups Mask.h"
#include "Bounds.h"
#include "Functions.h"
#include "Soft Body Mesh.h"
#include "Math.h"
#include "Scene.h"
#include "Ray.h"
#include "Physics Stream.h"
#include "Compartment.h"
#include "Core.h"
#include "Memory Reader Stream.h"
#include "Soft Body Split Pair Data.h"

#include <NxSoftBody.h> 

using namespace StillDesign::PhysX;

SoftBody::SoftBody( NxSoftBody* softBody, StillDesign::PhysX::MeshData^ meshData, SoftBodySplitPairData^ splitPairData )
{
	Debug::Assert( softBody != NULL );
	Debug::Assert( meshData != nullptr );
	Debug::Assert( splitPairData != nullptr );
	
	ObjectCache::Add( (intptr_t)softBody, this );
	
	_softBody = softBody;
	
	_scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&softBody->getScene()) );
	_mesh = ObjectCache::GetObject<StillDesign::PhysX::SoftBodyMesh^>( (intptr_t)softBody->getSoftBodyMesh() );
	_meshData = meshData;
	
	if( softBody->getCompartment() != NULL )
		_compartment = ObjectCache::GetObject<StillDesign::PhysX::Compartment^>( (intptr_t)softBody->getCompartment() );
	
	_splitPairData = splitPairData;
}
SoftBody::~SoftBody()
{
	this->!SoftBody();
}
SoftBody::!SoftBody()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	_scene->UnmanagedPointer->releaseSoftBody( *_softBody );
	
	_softBody = NULL;
	
	_scene = nullptr;
	_mesh = nullptr;
	_meshData = nullptr;
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool SoftBody::IsDisposed::get()
{
	return ( _softBody == NULL );
}

SoftBodyDescription^ SoftBody::SaveToDescription()
{
	NxSoftBodyDesc* desc = new NxSoftBodyDesc();
	
	if( _softBody->saveToDesc( *desc ) == false )
	{
		delete desc;
		return nullptr;
	}
	
	SoftBodyDescription^ d = gcnew SoftBodyDescription( desc, this->MeshData, this->SplitPairData );
		d->SoftBodyMesh = this->SoftBodyMesh;
		d->Compartment = this->Compartment;
		d->UserData = this->UserData;
	
	return d;
}

// Positions
array<Vector3>^ SoftBody::GetPositions()
{
	array<Vector3>^ positions = gcnew array<Vector3>( _softBody->getNumberOfParticles() );
	
	for( unsigned int x = 0; x < _softBody->getNumberOfParticles(); x++ )
	{
		positions[ x ] = Math::NxVec3ToVector3( _softBody->getPosition( x ) );
	}
	
	return positions;
}
void SoftBody::SetPositions( array<Vector3>^ value )
{
	ThrowIfNull( value, "value" );
	
	NxVec3* positions = new NxVec3[ value->Length ];
	
	// TODO Perhaps a pinned pointer and memcpy?
	for( int x = 0; x < value->Length; x++ )
	{
		positions[ x ] = Math::Vector3ToNxVec3( value[ x ] );
	}
	
	_softBody->setPositions( positions );
	
	delete[] positions;
	positions = NULL;
}
Vector3 SoftBody::GetPosition( int particleIndex )
{
	return Math::NxVec3ToVector3( _softBody->getPosition( particleIndex ) );
}
void SoftBody::SetPosition( int particleIndex, Vector3 position )
{
	_softBody->setPosition( Math::Vector3ToNxVec3( position ), particleIndex );
}

// Velocity
array<Vector3>^ SoftBody::GetVelocities()
{
	array<Vector3>^ velocities = gcnew array<Vector3>( _softBody->getNumberOfParticles() );
	
	for( unsigned int x = 0; x < _softBody->getNumberOfParticles(); x++ )
	{
		velocities[ x ] = Math::NxVec3ToVector3( _softBody->getVelocity( x ) );
	}
	
	return velocities;
}
void SoftBody::SetVelocities( array<Vector3>^ value )
{
	ThrowIfNull( value, "value" );
	
	NxVec3* velocities = new NxVec3[ value->Length ];
	
	for( int x = 0; x < value->Length; x++ )
	{
		velocities[ x ] = Math::Vector3ToNxVec3( value[ x ] );
	}
	
	_softBody->setVelocities( velocities );
	
	delete[] velocities;
	velocities = NULL;
}
Vector3 SoftBody::GetVelocity( int particleIndex )
{
	return Math::NxVec3ToVector3( _softBody->getVelocity( particleIndex ) );
}
void SoftBody::SetVelocity( int particleIndex, Vector3 velocity )
{
	_softBody->setVelocity( Math::Vector3ToNxVec3( velocity ), particleIndex );
}

void SoftBody::AttachToShape( Shape^ shape, SoftBodyAttachmentFlag attachmentFlags )
{
	ThrowIfNullOrDisposed( shape, "shape" );
	
	_softBody->attachToShape( shape->UnmanagedPointer, (NxU32)attachmentFlags );
}
void SoftBody::AttachToCollidingShapes( int attachmentFlags )
{
	_softBody->attachToCollidingShapes( attachmentFlags );
}
void SoftBody::DetachFromShape( Shape^ shape )
{
	_softBody->detachFromShape( shape->UnmanagedPointer );
}
void SoftBody::AttachVertexToShape( int vertexID, Shape^ shape, Vector3 localPosition, SoftBodyAttachmentFlag attachmentFlags )
{
	ThrowIfNullOrDisposed( shape, "shape" );
	
	_softBody->attachVertexToShape( vertexID, shape->UnmanagedPointer, Math::Vector3ToNxVec3( localPosition ), (NxU32)attachmentFlags );
}
void SoftBody::AttachVertexToGlobalPosition( int vertexID, Vector3 globalPosition )
{
	_softBody->attachVertexToGlobalPosition( vertexID, Math::Vector3ToNxVec3( globalPosition ) );
}
void SoftBody::FreeVertex( int vertexID )
{
	_softBody->freeVertex( vertexID );
}
void SoftBody::TearVertex( int vertexID, Vector3 normal )
{
	_softBody->tearVertex( vertexID, Math::Vector3ToNxVec3( normal ) );
}
SoftBody::SoftBodyRaycastResult^ SoftBody::Raycast( StillDesign::PhysX::Ray worldRay )
{
	NxVec3 h;
	NxU32 v;
	
	bool r = _softBody->raycast( (NxRay)worldRay, h, v );
	
	return gcnew SoftBody::SoftBodyRaycastResult( r, Math::NxVec3ToVector3( h ), v );
}

int SoftBody::QueryShapePointers()
{
	return _softBody->queryShapePointers();
}

array<Shape^>^ SoftBody::GetInteractingShapes()
{
	int i = this->QueryShapePointers();
	
	NxShape** s = new NxShape*[ i ];
	_softBody->getShapePointers( s, NULL );
	
	array<Shape^>^ shapes = gcnew array<Shape^>( i );
	
	for( int x = 0; x < i; x++ )
	{
		shapes[ i ] = ObjectCache::GetObject<Shape^>( (intptr_t)s[ i ] );
	}
	
	delete[] s;
	s = NULL;
	
	return shapes;
}
void SoftBody::SetInteractingShapes( array<Shape^>^ shapes )
{
	if( shapes == nullptr )
		throw gcnew ArgumentNullException( "shapes" );
	
	NxShape** s = new NxShape*[ shapes->Length ];
	for( int x = 0; x < shapes->Length; x++ )
	{
		if( shapes[ x ] == nullptr )
			throw gcnew InvalidOperationException( String::Format( "Shape {0} is null", x ) );
		if( shapes[ x ]->IsDisposed == true )
			throw gcnew InvalidOperationException( String::Format( "Shape {0} is disposed", x ) );
		
		s[ x ] = shapes[ x ]->UnmanagedPointer;
	}
	
	_softBody->setShapePointers( s, shapes->Length );
	
	delete[] s;
}

int SoftBody::GetStateByteSize()
{
	return _softBody->getStateByteSize();
}
void SoftBody::SaveStateToStream( Stream^ stream )
{
	return SaveStateToStream( stream, false );
}
void SoftBody::SaveStateToStream( Stream^ stream, bool permute )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanWrite == false )
		throw gcnew ArgumentException( "Stream is not writable", "stream" );
	
	_softBody->saveStateToStream( *(MemoryReaderStream::FromStream( stream )->UnmanagedPointer), permute );
}
void SoftBody::LoadStateFromStream( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Stream is not readable", "stream" );
	
	_softBody->loadStateFromStream( *(MemoryReaderStream::FromStream( stream )->UnmanagedPointer) );
}

StillDesign::PhysX::Scene^ SoftBody::Scene::get()
{
	return _scene;
}

StillDesign::PhysX::Compartment^ SoftBody::Compartment::get()
{
	return _compartment;
}

String^ SoftBody::Name::get()
{
	return Functions::UnmanagedToManagedString( _softBody->getName() );
}
void SoftBody::Name::set( String^ value )
{
	_softBody->setName( Functions::ManagedToUnmanagedString( value ) );
}

StillDesign::PhysX::SoftBodyMesh^ SoftBody::SoftBodyMesh::get()
{
	return _mesh;
}

float SoftBody::ParticleRadius::get()
{
	return _softBody->getParticleRadius();
}
void SoftBody::ParticleRadius::set( float value )
{
	_softBody->setParticleRadius( value );
}

int SoftBody::NumberOfParticles::get()
{
	return _softBody->getNumberOfParticles();
}

float SoftBody::Density::get()
{
	return _softBody->getDensity();
}

float SoftBody::VolumeStiffness::get()
{
	return _softBody->getVolumeStiffness();
}
void SoftBody::VolumeStiffness::set( float value )
{
	_softBody->setVolumeStiffness( value );
}

float SoftBody::StretchingStiffness::get()
{
	return _softBody->getStretchingStiffness();
}
void SoftBody::StretchingStiffness::set( float value )
{
	_softBody->setStretchingStiffness( value );
}

float SoftBody::DampingStiffness::get()
{
	return _softBody->getDampingCoefficient();
}
void SoftBody::DampingStiffness::set( float value )
{
	_softBody->setDampingCoefficient( value );
}

float SoftBody::Friction::get()
{
	return _softBody->getFriction();
}
void SoftBody::Friction::set( float value )
{
	_softBody->setFriction( value );
}

float SoftBody::TearFactor::get()
{
	return _softBody->getTearFactor();
}
void SoftBody::TearFactor::set( float value )
{
	_softBody->setTearFactor( value );
}

float SoftBody::CollisionResponseCoefficient::get()
{
	return _softBody->getCollisionResponseCoefficient();
}
void SoftBody::CollisionResponseCoefficient::set( float value )
{
	_softBody->setCollisionResponseCoefficient( value );
}

float SoftBody::AttachmentResponseCoefficient::get()
{
	return _softBody->getAttachmentResponseCoefficient();
}
void SoftBody::AttachmentResponseCoefficient::set( float value )
{
	_softBody->setAttachmentResponseCoefficient( value );
}

float SoftBody::AttachmentTearFactor::get()
{
	return _softBody->getAttachmentTearFactor();
}
void SoftBody::AttachmentTearFactor::set( float value )
{
	_softBody->setAttachmentTearFactor( value );
}
float SoftBody::ToFluidResponseCoefficient::get()
{
	return _softBody->getToFluidResponseCoefficient();
}
void SoftBody::ToFluidResponseCoefficient::set( float value )
{
	_softBody->setToFluidResponseCoefficient( value );
}

float SoftBody::FromFluidResponseCoefficient::get()
{
	return _softBody->getFromFluidResponseCoefficient();
}
void SoftBody::FromFluidResponseCoefficient::set( float value )
{
	_softBody->setFromFluidResponseCoefficient( value );
}

float SoftBody::MinimumAdhereVelocity::get()
{
	return _softBody->getMinAdhereVelocity();
}
void SoftBody::MinimumAdhereVelocity::set( float value )
{
	_softBody->setMinAdhereVelocity( value );
}

int SoftBody::SolverIterations::get()
{
	return _softBody->getSolverIterations();
}
void SoftBody::SolverIterations::set( int value )
{
	_softBody->setSolverIterations( value );
}

Vector3 SoftBody::ExternalAcceleration::get()
{
	return Math::NxVec3ToVector3( _softBody->getExternalAcceleration() );
}
void SoftBody::ExternalAcceleration::set( Vector3 value )
{
	_softBody->setExternalAcceleration( Math::Vector3ToNxVec3( value ) );
}

float SoftBody::SleepLinearVelocity::get()
{
	return _softBody->getSleepLinearVelocity();
}
void SoftBody::SleepLinearVelocity::set( float value )
{
	_softBody->setSleepLinearVelocity( value );
}

StillDesign::PhysX::MeshData^ SoftBody::MeshData::get()
{
	return _meshData;
}
void SoftBody::MeshData::set( StillDesign::PhysX::MeshData^ value )
{
	if( value == nullptr )
		throw gcnew ArgumentException( "MeshData cannot be null" );
	
	_softBody->setMeshData( *value->UnmanagedPointer );
	
	_meshData = value;
}

StillDesign::PhysX::GroupsMask SoftBody::GroupsMask::get()
{
	return (StillDesign::PhysX::GroupsMask)_softBody->getGroupsMask();
}
void SoftBody::GroupsMask::set( StillDesign::PhysX::GroupsMask value )
{
	_softBody->setGroupsMask( (NxGroupsMask)value );
}

SoftBodySplitPairData^ SoftBody::SplitPairData::get()
{
	return _splitPairData;
}

Bounds3 SoftBody::ValidBounds::get()
{
	NxBounds3 bounds;
	_softBody->getValidBounds( bounds );
	
	return (Bounds3)bounds;
}
void SoftBody::ValidBounds::set( Bounds3 value )
{
	_softBody->setValidBounds( (NxBounds3)value );
}

float SoftBody::RelativeGridSpacing::get()
{
	return _softBody->getRelativeGridSpacing();
}

SoftBodyFlag SoftBody::Flags::get()
{
	return (SoftBodyFlag)_softBody->getFlags();
}
void SoftBody::Flags::set( SoftBodyFlag value )
{
	_softBody->setFlags( (NxSoftBodyFlag)value );
}

Object^ SoftBody::UserData::get()
{
	return _userData;
}
void SoftBody::UserData::set( Object^ value )
{
	_userData = value;
}

NxSoftBody* SoftBody::UnmanagedPointer::get()
{
	return _softBody;
} 

//

SoftBody::SoftBodyRaycastResult::SoftBodyRaycastResult( bool hit, Vector3 hitPosition, int vertexID ) : RaycastResult( hit, hitPosition )
{
	_vertexID = vertexID;
}

int SoftBody::SoftBodyRaycastResult::VertexID::get()
{
	return _vertexID;
}