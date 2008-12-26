#include "StdAfx.h"

#include "Cloth.h"
#include "Cloth Description.h"
#include "Math.h"
#include "Functions.h"
#include "Scene.h"
#include "Shape.h"
#include "Ray.h"
#include "Actor.h"
#include "Mesh Data.h"
#include "Bounds.h"
#include "Groups Mask.h"
#include "Compartment.h"
#include "Memory Reader Stream.h"
#include "Memory Writer Stream.h"
#include "User Memory Writer Stream.h"
#include "Cloth Mesh.h"

#include <NxCloth.h> 
#include <NxClothDesc.h> 

using namespace System;
using namespace StillDesign::PhysX;

Cloth::Cloth( NxCloth* cloth, StillDesign::PhysX::MeshData^ meshData )
{
	Debug::Assert( cloth != NULL );
	Debug::Assert( meshData != nullptr );
	
	_cloth = cloth;
	
	_scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&cloth->getScene()) );
	
	_meshData = meshData;
	_clothMesh = ObjectCache::GetObject<StillDesign::PhysX::ClothMesh^>( (intptr_t)cloth->getClothMesh() );
	
	if( cloth->getCompartment() != NULL )
		_compartment = ObjectCache::GetObject<StillDesign::PhysX::Compartment^>( (intptr_t)cloth->getCompartment() );
	
	this->Flags |= ClothFlag::Visualization;
	
	ObjectCache::Add( (intptr_t)_cloth, this );
}
Cloth::~Cloth()
{
	this->!Cloth();
}
Cloth::!Cloth()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	_scene->UnmanagedPointer->releaseCloth( *_cloth );
	
	_cloth = NULL;
	
	_meshData = nullptr;
	_clothMesh = nullptr;
	
	_scene = nullptr;
	
	_userData = nullptr;
	
	OnDisposed( this, nullptr );
}
bool Cloth::IsDisposed::get()
{
	return ( _cloth == NULL );
}

//

ClothDescription^ Cloth::SaveToDescription()
{
	NxClothDesc* desc = new NxClothDesc();
	
	if( _cloth->saveToDesc( *desc ) == false )
	{
		delete desc;
		return nullptr;
	}
	
	ClothDescription^ clothDesc = gcnew ClothDescription( desc, this->MeshData );
		clothDesc->ClothMesh = this->ClothMesh;
		clothDesc->Compartment = this->Compartment;
		clothDesc->UserData = this->UserData;
	
	return clothDesc;
}
void Cloth::SaveStateToStream( Stream^ stream )
{
	SaveStateToStream( stream, false );
}
void Cloth::SaveStateToStream( Stream^ stream, bool permute )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanWrite == false )
		throw gcnew ArgumentException( "Cannot write to stream", "stream" );
	
	UserMemoryWriterStream writer;
	
	_cloth->saveStateToStream( writer, permute );
	
	array<Byte>^ buffer = gcnew array<Byte>( writer.currentSize );
	pin_ptr<Byte> b = &buffer[ 0 ];
	memcpy_s( b, writer.currentSize, writer.data, writer.currentSize );
	
	stream->Write( buffer, 0, writer.currentSize );
}
void Cloth::LoadStateFromStream( Stream^ stream )
{
	if( stream == nullptr )
		throw gcnew ArgumentNullException( "stream" );
	if( stream->CanRead == false )
		throw gcnew ArgumentException( "Cannot read from stream", "stream" );
	
	_cloth->loadStateFromStream( *(MemoryReaderStream::FromStream( stream )->UnmanagedPointer) );
}

// Forces
void Cloth::AddForceToVertex( Vector3 force, int vertexId )
{
	_cloth->addForceAtVertex( Math::Vector3ToNxVec3( force ), (NxU32)vertexId );
}
void Cloth::AddForceToVertex( Vector3 force, int vertexId, ForceMode forceMode )
{
	_cloth->addForceAtVertex( Math::Vector3ToNxVec3( force ), (NxU32)vertexId, (NxForceMode)forceMode );
}
void Cloth::AddForceAtPosition( Vector3 position, float magnitude, float radius )
{
	_cloth->addForceAtPos( Math::Vector3ToNxVec3( position ), magnitude, radius );
}
void Cloth::AddForceAtPosition( Vector3 position, float magnitude, float radius, ForceMode forceMode )
{
	_cloth->addForceAtPos( Math::Vector3ToNxVec3( position ), magnitude, radius, (NxForceMode)forceMode );
}
void Cloth::AddDirectedForceAtPosition( Vector3 position, Vector3 force, float radius )
{
	_cloth->addDirectedForceAtPos( Math::Vector3ToNxVec3( position ), Math::Vector3ToNxVec3( force ), radius );
}
void Cloth::AddDirectedForceAtPosition( Vector3 position, Vector3 force, float radius, ForceMode forceMode )
{
	_cloth->addDirectedForceAtPos( Math::Vector3ToNxVec3( position ), Math::Vector3ToNxVec3( force ), radius, (NxForceMode)forceMode );
}

void Cloth::AttachToShape( Shape^ shape, ClothAttachmentFlag attachmentFlags )
{
	ThrowIfNullOrDisposed( shape, "shape" );
	
	_cloth->attachToShape( shape->UnmanagedPointer, (NxU32)attachmentFlags );
}
void Cloth::AttachToCollidingShapes( ClothAttachmentFlag attachmentFlags )
{
	_cloth->attachToCollidingShapes( (NxU32)attachmentFlags );
}
void Cloth::DetachFromShape( Shape^ shape )
{
	ThrowIfNullOrDisposed( shape, "shape" );
	
	_cloth->detachFromShape( shape->UnmanagedPointer );
}
void Cloth::AttachVertexToShape( int vertexIndex, Shape^ shape, Vector3 localPosition, ClothAttachmentFlag attachmentFlags )
{
	ThrowIfNullOrDisposed( shape, "shape" );
	
	_cloth->attachVertexToShape( vertexIndex, shape->UnmanagedPointer, Math::Vector3ToNxVec3( localPosition ), (NxU32)attachmentFlags );
}
void Cloth::AttachVertexToGlobalPosition( int vertexIndex, Vector3 position )
{
	_cloth->attachVertexToGlobalPosition( vertexIndex, Math::Vector3ToNxVec3( position ) );
}
void Cloth::FreeVertex( int vertexIndex )
{
	_cloth->freeVertex( vertexIndex );
}
void Cloth::AttachToCore( Actor^ actor, float impulseThreshold )
{
	ThrowIfNullOrDisposed( actor, "actor" );
	
	_cloth->attachToCore( actor->UnmanagedPointer, impulseThreshold );
}
void Cloth::AttachToCore( Actor^ actor, float impulseThreshold, float penetrationDepth )
{
	_cloth->attachToCore( actor->UnmanagedPointer, impulseThreshold, penetrationDepth );
}
void Cloth::TearVertex( int vertexIndex, Vector3 normal )
{
	_cloth->tearVertex( vertexIndex, Math::Vector3ToNxVec3( normal ) );
}
ClothRaycastResult^ Cloth::Raycast( StillDesign::PhysX::Ray worldRay )
{
	NxVec3 hit;
	NxU32 vertexId;
	
	bool i = _cloth->raycast( (NxRay)worldRay, hit, vertexId );
	
	return gcnew ClothRaycastResult( i, Math::NxVec3ToVector3( hit ), (int)vertexId );
}
array<int>^ Cloth::OverlapAABBTriangles( Bounds3 bounds )
{
	NxU32 c;
	const NxU32* i;
	bool r = _cloth->overlapAABBTriangles( (NxBounds3)bounds, c, i );
	
	array<int>^ indices = gcnew array<int>( c );
	for( NxU32 x = 0; x < c; x++ )
	{
		indices[ x ] = (int)(*i);
		
		i++;
	}
	
	i = NULL;
	delete i;
	
	return r ? indices : nullptr;
}

int Cloth::QueryShapePointers()
{
	return _cloth->queryShapePointers();
}
int Cloth::GetStateSizeInByte()
{
	return _cloth->getStateByteSize();
}

void Cloth::WakeUp()
{
	_cloth->wakeUp();
}	
void Cloth::WakeUp( float wakeCounterValue )
{
	_cloth->wakeUp( wakeCounterValue );
}
void Cloth::Sleep()
{
	_cloth->putToSleep();
}

void Cloth::DominateVertex( int vertexID, float expirationTime, float dominanceWeight )
{
	_cloth->dominateVertex( vertexID, expirationTime, dominanceWeight );
}
ClothVertexAttachmentStatus Cloth::GetVertexAttachmentStatus( int vertexID )
{
	return (ClothVertexAttachmentStatus)_cloth->getVertexAttachmentStatus( vertexID );
}
Shape^ Cloth::GetVertexAttachmentShape( int vertexID )
{
	NxShape* s = _cloth->getVertexAttachmentShape( vertexID );
	
	if( s == NULL )
		return nullptr;
	else
		return ObjectCache::GetObject<Shape^>( (intptr_t)s );
}
Vector3 Cloth::GetVertexAttachmentPosition( int vertexID )
{
	return Math::NxVec3ToVector3( _cloth->getVertexAttachmentPosition( vertexID ) );
}

Vector3 Cloth::GetVertexPosition( int vertexID )
{
	return Math::NxVec3ToVector3( _cloth->getPosition( vertexID ) );
}
void Cloth::SetVertexPosition( int vertexID, Vector3 position )
{
	_cloth->setPosition( Math::Vector3ToNxVec3( position ), vertexID );
}
Vector3 Cloth::GetVertexVelocity( int vertexID )
{
	return Math::NxVec3ToVector3( _cloth->getVelocity( vertexID ) );
}
void Cloth::SetVertexVelocity( int vertexID, Vector3 velocity )
{
	_cloth->setVelocity( Math::Vector3ToNxVec3( velocity ), vertexID );
}

//

StillDesign::PhysX::Scene^ Cloth::Scene::get()
{
	return _scene;
}

String^ Cloth::Name::get()
{
	return Functions::UnmanagedToManagedString( _cloth->getName() );
}
void Cloth::Name::set( String^ value )
{
	_cloth->setName( Functions::ManagedToUnmanagedString( value ) );
}

StillDesign::PhysX::MeshData^ Cloth::MeshData::get()
{
	return _meshData;
}

StillDesign::PhysX::ClothMesh^ Cloth::ClothMesh::get()
{
	return _clothMesh;
}

StillDesign::PhysX::Compartment^ Cloth::Compartment::get()
{
	return _compartment;
}

array<Vector3>^ Cloth::ParticlePositions::get()
{
	int c = _cloth->getNumberOfParticles();
	
	NxVec3* buffer = (NxVec3*)malloc( sizeof( NxVec3 ) * c );
	Debug::Assert( buffer != NULL );
	
	array<Vector3>^ positions = gcnew array<Vector3>( c );
	
	_cloth->getPositions( buffer );
	
	for( int x = 0; x < c; x++ )
	{
		NxVec3* p = buffer + x;
		
		positions[ x ] = Math::NxVec3ToVector3( *p );
	}
	
	free( buffer );
	
	return positions;
}
void Cloth::ParticlePositions::set( array<Vector3>^ value )
{
	ThrowIfNull( value, "value" );
	
	if( value->Length != _cloth->getNumberOfParticles() )
		throw gcnew ArgumentException( "Length of positions array does not match the number of particles in the cloth" );
	
	int c = value->Length;
	
	NxVec3* buffer = (NxVec3*)malloc( sizeof( NxVec3 ) * c );
	Debug::Assert( buffer != NULL );
	
	for( int x = 0; x < c; x++ )
	{
		buffer[ x ] = Math::Vector3ToNxVec3( value[ x ] );
	}
	
	_cloth->setPositions( buffer );
	
	free( buffer );
}

array<Vector3>^ Cloth::ParticleVelocities::get()
{
	int c = _cloth->getNumberOfParticles();
	
	NxVec3* buffer = (NxVec3*)malloc( sizeof( NxVec3 ) * c );
	Debug::Assert( buffer != NULL );
	
	array<Vector3>^ velocities = gcnew array<Vector3>( c );
	
	_cloth->getVelocities( buffer );
	
	for( int x = 0; x < c; x++ )
	{
		NxVec3* p = buffer + x;
		
		velocities[ x ] = Math::NxVec3ToVector3( *p );
	}
	
	free( buffer );
	
	return velocities;
}
void Cloth::ParticleVelocities::set( array<Vector3>^ value )
{
	ThrowIfNull( value, "value" );
	
	if( value->Length != _cloth->getNumberOfParticles() )
		throw gcnew ArgumentException( "Length of velocities array does not match number of particles in the cloth" );
	
	int c = value->Length;
	
	NxVec3* buffer = (NxVec3*)malloc( sizeof( NxVec3 ) * c );
	Debug::Assert( buffer != NULL );
	
	for( int x = 0; x < c; x++ )
	{
		buffer[ x ] = Math::Vector3ToNxVec3( value[ x ] );
	}
	
	_cloth->setVelocities( buffer );
	
	free( buffer );
	buffer = NULL;
}
int Cloth::ParticleCount::get()
{
	return _cloth->getNumberOfParticles();
}

short Cloth::Group::get()
{
	return _cloth->getGroup();
}
void Cloth::Group::set( short value )
{
	_cloth->setGroup( value );
}

StillDesign::PhysX::GroupsMask Cloth::GroupsMask::get()
{
	return (StillDesign::PhysX::GroupsMask)_cloth->getGroupsMask();
}
void Cloth::GroupsMask::set( StillDesign::PhysX::GroupsMask value )
{
	_cloth->setGroupsMask( (NxGroupsMask)value );
}

ClothFlag Cloth::Flags::get()
{
	return (ClothFlag)_cloth->getFlags();
}
void Cloth::Flags::set( ClothFlag value )
{
	_cloth->setFlags( (NxClothFlag)value );
}

float Cloth::Thickness::get()
{
	return _cloth->getThickness();
}
void Cloth::Thickness::set( float value )
{
	_cloth->setThickness( value );
}

float Cloth::Density::get()
{
	return _cloth->getDensity();
}

float Cloth::RelativeGridSpacing::get()
{
	return _cloth->getRelativeGridSpacing();
}

float Cloth::BendingStiffness::get()
{
	return _cloth->getBendingStiffness();
}
void Cloth::BendingStiffness::set( float value )
{
	_cloth->setBendingStiffness( value );
}

float Cloth::StretchingStiffness::get()
{
	return _cloth->getStretchingStiffness();
}
void Cloth::StretchingStiffness::set( float value )
{
	_cloth->setStretchingStiffness( value );
}

float Cloth::DampingCoefficient::get()
{
	return _cloth->getDampingCoefficient();
}
void Cloth::DampingCoefficient::set( float value )
{
	_cloth->setDampingCoefficient( value );
}

float Cloth::Friction::get()
{
	return _cloth->getFriction();
}
void Cloth::Friction::set( float value )
{
	_cloth->setFriction( value );
}

float Cloth::Pressure::get()
{
	return _cloth->getPressure();
}
void Cloth::Pressure::set( float value )
{
	_cloth->setPressure( value );
}

float Cloth::TearFactor::get()
{
	return _cloth->getTearFactor();
}
void Cloth::TearFactor::set( float value )
{
	_cloth->setTearFactor( value );
}

float Cloth::AttachmentTearFactor::get()
{
	return _cloth->getAttachmentTearFactor();
}
void Cloth::AttachmentTearFactor::set( float value )
{
	_cloth->setAttachmentTearFactor( value );
}

float Cloth::CollisionResponceCoefficient::get()
{
	return _cloth->getCollisionResponseCoefficient();
}
void Cloth::CollisionResponceCoefficient::set( float value )
{
	_cloth->setCollisionResponseCoefficient( value );
}

float Cloth::AttachmentResponseCoefficient::get()
{
	return _cloth->getAttachmentResponseCoefficient();
}
void Cloth::AttachmentResponseCoefficient::set( float value )
{
	_cloth->setAttachmentResponseCoefficient( value );
}

float Cloth::FromFluidResponseCoefficient::get()
{
	return _cloth->getFromFluidResponseCoefficient();
}
void Cloth::FromFluidResponseCoefficient::set( float value )
{
	_cloth->setFromFluidResponseCoefficient( value );
}
float Cloth::ToFluidResponseCoefficient::get()
{
	return _cloth->getToFluidResponseCoefficient();
}
void Cloth::ToFluidResponseCoefficient::set( float value )
{
	_cloth->setToFluidResponseCoefficient( value );
}

float Cloth::MinimumAdhereVelocity::get()
{
	return _cloth->getMinAdhereVelocity();
}
void Cloth::MinimumAdhereVelocity::set( float value )
{
	_cloth->setMinAdhereVelocity( value );
}

int Cloth::SolverIterations::get()
{
	return _cloth->getSolverIterations();
}
void Cloth::SolverIterations::set( int value )
{
	_cloth->setSolverIterations( value );
}

Vector3 Cloth::ExternalAcceleration::get()
{
	return Math::NxVec3ToVector3( _cloth->getExternalAcceleration() );
}
void Cloth::ExternalAcceleration::set( Vector3 value )
{
	_cloth->setExternalAcceleration( Math::Vector3ToNxVec3( value ) );
}

Vector3 Cloth::WindAcceleration::get()
{
	return Math::NxVec3ToVector3( _cloth->getWindAcceleration() );
}
void Cloth::WindAcceleration::set( Vector3 value )
{
	_cloth->setWindAcceleration( Math::Vector3ToNxVec3( value ) );
}

float Cloth::SleepLinearVelocity::get()
{
	return _cloth->getSleepLinearVelocity();
}
void Cloth::SleepLinearVelocity::set( float value )
{
	_cloth->setSleepLinearVelocity( value );
}

Bounds3 Cloth::ValidBounds::get()
{
	NxBounds3 bounds;
	_cloth->getValidBounds( bounds );
	
	return (Bounds3)bounds;
}
void Cloth::ValidBounds::set( Bounds3 value )
{
	_cloth->setValidBounds( (NxBounds3)value );
}

Bounds3 Cloth::WorldBounds::get()
{
	NxBounds3 bounds;
	_cloth->getWorldBounds( bounds );
	
	return (Bounds3)bounds;
}

bool Cloth::IsSleeping::get()
{
	return _cloth->isSleeping();
}

Object^ Cloth::UserData::get()
{
	return _userData;
}
void Cloth::UserData::set( Object^ value )
{
	_userData = value;
}

NxCloth* Cloth::UnmanagedPointer::get()
{
	return _cloth;
}

///////////////////
// Cloth Ray Cast Result
///////////////////

ClothRaycastResult::ClothRaycastResult( bool rayHit, Vector3 hitPosition, int vertexIndex ) : RaycastResult( rayHit, hitPosition )
{
	_vertexIndex = vertexIndex;
}

int ClothRaycastResult::VertexIndex::get()
{
	return _vertexIndex;
}