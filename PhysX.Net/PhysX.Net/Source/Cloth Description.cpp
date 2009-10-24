#include "StdAfx.h"

#include "Cloth Description.h"
#include "Math.h"
#include "Functions.h"
#include "Cloth.h"
#include "Cloth Mesh.h"
#include "Mesh Data.h"
#include "Groups Mask.h"
#include "Bounds.h"
#include "Core.h"
#include "Compartment.h"
#include "Cloth Split Pair Data.h"

#include <NxCloth.h> 
#include <NxClothDesc.h> 

using namespace StillDesign::PhysX;

ClothDescription::ClothDescription()
{
	_clothDesc = new NxClothDesc();
	
	_meshData = gcnew StillDesign::PhysX::MeshData( &_clothDesc->meshData );
	
	Create();
}
ClothDescription::ClothDescription( NxClothDesc* description, StillDesign::PhysX::MeshData^ meshData )
{
	Debug::Assert( description != NULL );
	
	_clothDesc = description;
	
	if( description->clothMesh != NULL )
		_clothMesh = ObjectTable::GetObject<StillDesign::PhysX::ClothMesh^>( (intptr_t)description->clothMesh );
	
	_meshData = meshData;
	
	Create();
}
ClothDescription::~ClothDescription()
{
	this->!ClothDescription();
}
ClothDescription::!ClothDescription()
{
	if( this->IsDisposed == true )
		return;
	
	OnDisposing( this, nullptr );
	
	SAFE_DELETE( _clothDesc );
	
	_clothMesh = nullptr;
	_meshData = nullptr;
	
	_userData = nullptr;
	
	OnDisposed( this, nullptr );
}
void ClothDescription::Create()
{
	_splitPairData = gcnew ClothSplitPairData( &_clothDesc->splitPairData );
}
bool ClothDescription::IsDisposed::get()
{
	return ( _clothDesc == NULL );
}

bool ClothDescription::IsValid()
{
	return _clothDesc->isValid();
}
void ClothDescription::SetToDefault()
{
	_clothDesc->setToDefault();
	
	_clothMesh = nullptr;
	_meshData = nullptr;
	
	_compartment = nullptr;
}

String^ ClothDescription::Name::get()
{
	return Functions::UnmanagedToManagedString( _clothDesc->name );
}
void ClothDescription::Name::set( String^ value )
{
	_clothDesc->name = Functions::ManagedToUnmanagedString( value );
}

ClothFlag ClothDescription::Flags::get()
{
	return (ClothFlag)_clothDesc->flags;
}
void ClothDescription::Flags::set( ClothFlag value )
{
	_clothDesc->flags = (NxClothFlag)value;
}

StillDesign::PhysX::ClothMesh^ ClothDescription::ClothMesh::get()
{
	return _clothMesh;
}
void ClothDescription::ClothMesh::set( StillDesign::PhysX::ClothMesh^ value )
{
	_clothMesh = value;
	
	if( value == nullptr )
		_clothDesc->clothMesh = NULL;
	else
		_clothDesc->clothMesh = value->UnmanagedPointer;
}
StillDesign::PhysX::MeshData^ ClothDescription::MeshData::get()
{
	return _meshData;
}

StillDesign::PhysX::Compartment^ ClothDescription::Compartment::get()
{
	return _compartment;
}
void ClothDescription::Compartment::set( StillDesign::PhysX::Compartment^ value )
{
	_compartment = value;
	
	if( value != nullptr )
		_clothDesc->compartment = value->UnmanagedPointer;
	else
		_clothDesc->compartment = NULL;
}

Matrix ClothDescription::GlobalPose::get()
{
	return Math::Mat34ToMatrix( &_clothDesc->globalPose );
}
void ClothDescription::GlobalPose::set( Matrix value )
{
	_clothDesc->globalPose = Math::MatrixToMat34( value );
}

float ClothDescription::Thickness::get()
{
	return _clothDesc->thickness;
}
void ClothDescription::Thickness::set( float value )
{
	_clothDesc->thickness = value;
}
float ClothDescription::SelfCollisionThickness::get()
{
	return _clothDesc->selfCollisionThickness;
}
void ClothDescription::SelfCollisionThickness::set( float value )
{
	_clothDesc->selfCollisionThickness = value;
}

float ClothDescription::Density::get()
{
	return _clothDesc->density;
}
void ClothDescription::Density::set( float value )
{
	_clothDesc->density = value;
}

float ClothDescription::BendingStiffness::get()
{
	return _clothDesc->bendingStiffness;
}
void ClothDescription::BendingStiffness::set( float value )
{
	_clothDesc->bendingStiffness = value;
}

float ClothDescription::StretchingStiffness::get()
{
	return _clothDesc->stretchingStiffness;
}
void ClothDescription::StretchingStiffness::set( float value )
{
	_clothDesc->stretchingStiffness = value;
}

float ClothDescription::DampingCoefficient::get()
{
	return _clothDesc->dampingCoefficient;
}
void ClothDescription::DampingCoefficient::set( float value )
{
	_clothDesc->dampingCoefficient = value;
}

float ClothDescription::Friction::get()
{
	return _clothDesc->friction;
}
void ClothDescription::Friction::set( float value )
{
	_clothDesc->friction = value;
}

float ClothDescription::Pressure::get()
{
	return _clothDesc->pressure;
}
void ClothDescription::Pressure::set( float value )
{
	_clothDesc->pressure = value;
}

float ClothDescription::TearFactor::get()
{
	return _clothDesc->tearFactor;
}
void ClothDescription::TearFactor::set( float value )
{
	_clothDesc->tearFactor = value;
}

float ClothDescription::CollisionResponceCoefficient::get()
{
	return _clothDesc->collisionResponseCoefficient;
}
void ClothDescription::CollisionResponceCoefficient::set( float value )
{
	_clothDesc->collisionResponseCoefficient = value;
}

float ClothDescription::AttachmentResponseCoefficient::get()
{
	return _clothDesc->attachmentResponseCoefficient;
}
void ClothDescription::AttachmentResponseCoefficient::set( float value )
{
	_clothDesc->attachmentResponseCoefficient = value;
}

float ClothDescription::AttachmentTearFactor::get()
{
	return _clothDesc->attachmentTearFactor;
}
void ClothDescription::AttachmentTearFactor::set( float value )
{
	_clothDesc->attachmentTearFactor = value;
}

float ClothDescription::ToFluidResponseCoefficent::get()
{
	return _clothDesc->toFluidResponseCoefficient;
}
void ClothDescription::ToFluidResponseCoefficent::set( float value )
{
	_clothDesc->toFluidResponseCoefficient = value;
}

float ClothDescription::FromFluidResponseCoefficent::get()
{
	return _clothDesc->fromFluidResponseCoefficient;
}
void ClothDescription::FromFluidResponseCoefficent::set( float value )
{
	_clothDesc->fromFluidResponseCoefficient = value;
}

float ClothDescription::MinimumAdhereVelocity::get()
{
	return _clothDesc->minAdhereVelocity;
}
void ClothDescription::MinimumAdhereVelocity::set( float value )
{
	_clothDesc->minAdhereVelocity = value;
}

int ClothDescription::SolverIterations::get()
{
	return _clothDesc->solverIterations;
}
void ClothDescription::SolverIterations::set( int value )
{
	_clothDesc->solverIterations = value;
}

Vector3 ClothDescription::ExternalAcceleration::get()
{
	return Math::NxVec3ToVector3( _clothDesc->externalAcceleration );
}
void ClothDescription::ExternalAcceleration::set( Vector3 value )
{
	_clothDesc->externalAcceleration = Math::Vector3ToNxVec3( value );
}

Vector3 ClothDescription::WindAcceleration::get()
{
	return Math::NxVec3ToVector3( _clothDesc->windAcceleration );
}
void ClothDescription::WindAcceleration::set( Vector3 value )
{
	_clothDesc->windAcceleration = Math::Vector3ToNxVec3( value );
}

float ClothDescription::WakeUpCounter::get()
{
	return _clothDesc->wakeUpCounter;
}
void ClothDescription::WakeUpCounter::set( float value )
{
	_clothDesc->wakeUpCounter = value;
}

float ClothDescription::SleepLinearVelocity::get()
{
	return _clothDesc->sleepLinearVelocity;
}
void ClothDescription::SleepLinearVelocity::set( float value )
{
	_clothDesc->sleepLinearVelocity = value;
}

short ClothDescription::CollisionGroup::get()
{
	return _clothDesc->collisionGroup;
}
void ClothDescription::CollisionGroup::set( short value )
{
	_clothDesc->collisionGroup = value;
}
StillDesign::PhysX::GroupsMask ClothDescription::GroupsMask::get()
{
	return (StillDesign::PhysX::GroupsMask)_clothDesc->groupsMask;
}
void ClothDescription::GroupsMask::set( StillDesign::PhysX::GroupsMask value )
{
	_clothDesc->groupsMask = (NxGroupsMask)value;
}

short ClothDescription::ForceFieldMaterial::get()
{
	return _clothDesc->forceFieldMaterial;
}
void ClothDescription::ForceFieldMaterial::set( short value )
{
	_clothDesc->forceFieldMaterial = value;
}

Bounds3 ClothDescription::ValidBounds::get()
{
	return (Bounds3)_clothDesc->validBounds;
}
void ClothDescription::ValidBounds::set( Bounds3 value )
{
	_clothDesc->validBounds = (NxBounds3)value;
}

float ClothDescription::RelativeGridSpacing::get()
{
	return _clothDesc->relativeGridSpacing;
}
void ClothDescription::RelativeGridSpacing::set( float value )
{
	_clothDesc->relativeGridSpacing = value;
}

int ClothDescription::HierarchicalSolverIterations::get()
{
	return this->UnmanagedPointer->hierarchicalSolverIterations;
}
void ClothDescription::HierarchicalSolverIterations::set( int value )
{
	this->UnmanagedPointer->hierarchicalSolverIterations = value;
}

float ClothDescription::HardStretchLimitationFactor::get()
{
	return this->UnmanagedPointer->hardStretchLimitationFactor;
}
void ClothDescription::HardStretchLimitationFactor::set( float value )
{
	this->UnmanagedPointer->hardStretchLimitationFactor = value;
}

ClothSplitPairData^ ClothDescription::SplitPairData::get()
{
	return _splitPairData;
}

Object^ ClothDescription::UserData::get()
{
	return _userData;
}
void ClothDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxClothDesc* ClothDescription::UnmanagedPointer::get()
{
	return _clothDesc;
}