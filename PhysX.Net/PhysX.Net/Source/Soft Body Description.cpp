#include "StdAfx.h"

#include "Soft Body Description.h"
#include "Mesh Data.h"
#include "Groups Mask.h"
#include "Bounds.h"
#include "Functions.h"
#include "Soft Body Mesh.h"
#include "Math.h"
#include "Compartment.h"
#include "Soft Body Split Pair Data.h"

#include <NxSoftBodyDesc.h> 

using namespace StillDesign::PhysX;

SoftBodyDescription::SoftBodyDescription()
{
	_desc = new NxSoftBodyDesc();
	
	//_meshData = gcnew StillDesign::PhysX::MeshData( &_desc->meshData );
	_splitPairData = gcnew SoftBodySplitPairData();
}
SoftBodyDescription::SoftBodyDescription( NxSoftBodyDesc* desc, StillDesign::PhysX::MeshData^ meshData, StillDesign::PhysX::SoftBodySplitPairData^ splitPairData )
{
	Debug::Assert( desc != NULL );
	ThrowIfDisposed( meshData, "meshData" );
	
	_desc = desc;
	if( desc->softBodyMesh != NULL )
		_mesh = ObjectTable::GetObject<StillDesign::PhysX::SoftBodyMesh^>( (intptr_t)desc->softBodyMesh );
	if( desc->compartment != NULL )
		_compartment = ObjectTable::GetObject<StillDesign::PhysX::Compartment^>( (intptr_t)desc->compartment );
	_meshData = meshData;
	_splitPairData = splitPairData;
}
SoftBodyDescription::~SoftBodyDescription()
{
	this->!SoftBodyDescription();
}
SoftBodyDescription::!SoftBodyDescription()
{
	SAFE_DELETE( _desc );
	
	_mesh = nullptr;
	_meshData = nullptr;
	_splitPairData = nullptr;
	_compartment = nullptr;
}

void SoftBodyDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_mesh = nullptr;
	_meshData->SetToDefault();
	_splitPairData = nullptr;
	
	_compartment = nullptr;
	
	_userData = nullptr;
}
bool SoftBodyDescription::IsValid()
{
	return _desc->isValid();
}
int SoftBodyDescription::CheckValid()
{
	return _desc->checkValid();
}

String^ SoftBodyDescription::Name::get()
{
	return Functions::UnmanagedToManagedString( _desc->name );
}
void SoftBodyDescription::Name::set( String^ value )
{
	_desc->name = Functions::ManagedToUnmanagedString( value );
}

StillDesign::PhysX::SoftBodyMesh^ SoftBodyDescription::SoftBodyMesh::get()
{
	return _mesh;
}
void SoftBodyDescription::SoftBodyMesh::set( StillDesign::PhysX::SoftBodyMesh^ value )
{
	_mesh = value;
	
	if( value == nullptr )
		_desc->softBodyMesh = NULL;
	else
		_desc->softBodyMesh = value->UnmanagedPointer;
}

StillDesign::PhysX::Compartment^ SoftBodyDescription::Compartment::get()
{
	return _compartment;
}
void SoftBodyDescription::Compartment::set( StillDesign::PhysX::Compartment^ value )
{
	_compartment = value;
	
	if( value != nullptr )
		_desc->compartment = value->UnmanagedPointer;
	else
		_desc->compartment = NULL;
}

Matrix SoftBodyDescription::GlobalPose::get()
{
	return Math::Mat34ToMatrix( &_desc->globalPose );
}
void SoftBodyDescription::GlobalPose::set( Matrix value )
{
	_desc->globalPose = Math::MatrixToMat34( value );
}

float SoftBodyDescription::ParticleRadius::get()
{
	return _desc->particleRadius;
}
void SoftBodyDescription::ParticleRadius::set( float value )
{
	_desc->particleRadius = value;
}

float SoftBodyDescription::Density::get()
{
	return _desc->density;
}
void SoftBodyDescription::Density::set( float value )
{
	_desc->density = value;
}

float SoftBodyDescription::VolumeStiffness::get()
{
	return _desc->volumeStiffness;
}
void SoftBodyDescription::VolumeStiffness::set( float value )
{
	_desc->volumeStiffness = value;
}

float SoftBodyDescription::StretchingStiffness::get()
{
	return _desc->stretchingStiffness;
}
void SoftBodyDescription::StretchingStiffness::set( float value )
{
	_desc->stretchingStiffness = value;
}

float SoftBodyDescription::DampingStiffness::get()
{
	return _desc->dampingCoefficient;
}
void SoftBodyDescription::DampingStiffness::set( float value )
{
	_desc->dampingCoefficient = value;
}

float SoftBodyDescription::Friction::get()
{
	return _desc->friction;
}
void SoftBodyDescription::Friction::set( float value )
{
	_desc->friction = value;
}

float SoftBodyDescription::TearFactor::get()
{
	return _desc->tearFactor;
}
void SoftBodyDescription::TearFactor::set( float value )
{
	_desc->tearFactor = value;
}

float SoftBodyDescription::CollisionResponseCoefficient::get()
{
	return _desc->collisionResponseCoefficient;
}
void SoftBodyDescription::CollisionResponseCoefficient::set( float value )
{
	_desc->collisionResponseCoefficient = value;
}

float SoftBodyDescription::AttachmentResponseCoefficient::get()
{
	return _desc->attachmentResponseCoefficient;
}
void SoftBodyDescription::AttachmentResponseCoefficient::set( float value )
{
	_desc->attachmentResponseCoefficient = value;
}

float SoftBodyDescription::AttachmentTearFactor::get()
{
	return _desc->attachmentTearFactor;
}
void SoftBodyDescription::AttachmentTearFactor::set( float value )
{
	_desc->attachmentTearFactor = value;
}
float SoftBodyDescription::ToFluidResponseCoefficient::get()
{
	return _desc->toFluidResponseCoefficient;
}
void SoftBodyDescription::ToFluidResponseCoefficient::set( float value )
{
	_desc->toFluidResponseCoefficient = value;
}

float SoftBodyDescription::FromFluidResponseCoefficient::get()
{
	return _desc->fromFluidResponseCoefficient;
}
void SoftBodyDescription::FromFluidResponseCoefficient::set( float value )
{
	_desc->fromFluidResponseCoefficient = value;
}

float SoftBodyDescription::MinimumAdhereVelocity::get()
{
	return _desc->minAdhereVelocity;
}
void SoftBodyDescription::MinimumAdhereVelocity::set( float value )
{
	_desc->minAdhereVelocity = value;
}

int SoftBodyDescription::SolverIterations::get()
{
	return _desc->solverIterations;
}
void SoftBodyDescription::SolverIterations::set( int value )
{
	_desc->solverIterations = value;
}

Vector3 SoftBodyDescription::ExternalAcceleration::get()
{
	return Math::NxVec3ToVector3( _desc->externalAcceleration );
}
void SoftBodyDescription::ExternalAcceleration::set( Vector3 value )
{
	_desc->externalAcceleration = Math::Vector3ToNxVec3( value );
}

float SoftBodyDescription::WakeUpCounter::get()
{
	return _desc->wakeUpCounter;
}
void SoftBodyDescription::WakeUpCounter::set( float value )
{
	_desc->wakeUpCounter = value;
}

float SoftBodyDescription::SleepLinearVelocity::get()
{
	return _desc->sleepLinearVelocity;
}
void SoftBodyDescription::SleepLinearVelocity::set( float value )
{
	_desc->sleepLinearVelocity = value;
}

StillDesign::PhysX::MeshData^ SoftBodyDescription::MeshData::get()
{
	return _meshData;
}

short SoftBodyDescription::CollisionGroup::get()
{
	return _desc->collisionGroup;
}
void SoftBodyDescription::CollisionGroup::set( short value )
{
	_desc->collisionGroup = value;
}

StillDesign::PhysX::GroupsMask SoftBodyDescription::GroupsMask::get()
{
	return (StillDesign::PhysX::GroupsMask)_desc->groupsMask;
}
void SoftBodyDescription::GroupsMask::set( StillDesign::PhysX::GroupsMask value )
{
	_desc->groupsMask = (NxGroupsMask)value;
}

SoftBodySplitPairData^ SoftBodyDescription::SplitPairData::get()
{
	return _splitPairData;
}

short SoftBodyDescription::ForceFieldMaterial::get()
{
	return _desc->forceFieldMaterial;
}
void SoftBodyDescription::ForceFieldMaterial::set( short value )
{
	_desc->forceFieldMaterial = value;
}

Bounds3 SoftBodyDescription::ValidBounds::get()
{
	return (Bounds3)_desc->validBounds;
}
void SoftBodyDescription::ValidBounds::set( Bounds3 value )
{
	_desc->validBounds = (NxBounds3)value;
}
float SoftBodyDescription::RelativeGridSpacing::get()
{
	return _desc->relativeGridSpacing;
}
void SoftBodyDescription::RelativeGridSpacing::set( float value )
{
	_desc->relativeGridSpacing = value;
}

SoftBodyFlag SoftBodyDescription::Flags::get()
{
	return (SoftBodyFlag)_desc->flags;
}
void SoftBodyDescription::Flags::set( SoftBodyFlag value )
{
	_desc->flags = (NxSoftBodyFlag)value;
}

float SoftBodyDescription::SelfCollisionThickness::get()
{
	return _desc->selfCollisionThickness;
}
void SoftBodyDescription::SelfCollisionThickness::set( float value )
{
	_desc->selfCollisionThickness = value;
}

Object^ SoftBodyDescription::UserData::get()
{
	return _userData;
}
void SoftBodyDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxSoftBodyDesc* SoftBodyDescription::UnmanagedPointer::get()
{
	return _desc;
}