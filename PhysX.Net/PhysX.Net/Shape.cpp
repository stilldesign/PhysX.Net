#include "StdAfx.h"

#include "Base Shape.h"
#include "Material.h"
#include "Actor.h"
#include "Scene.h"
#include "Material.h"
#include "Box Shape.h"
#include "Bounds.h"
#include "Functions.h"
#include "Shape Description.h"
#include "Math.h"
#include "Capsule.h"
#include "Box.h"
#include "Groups Mask.h"
#include "Ray.h"
#include "Raycast Hit.h"
#include "CCD Skeleton.h"
#include "Sphere.h"

using namespace System;
using namespace StillDesign;
using namespace StillDesign::PhysX;

// Shape
Shape::Shape( NxShape* shape )
{
	Debug::Assert( shape != NULL );
	
	_shape = shape;
	
	_actor = ObjectCache::GetObject<StillDesign::PhysX::Actor^>( (intptr_t)(&shape->getActor()) );
	
	{
		// Assign Managed Material
		NxMaterial* material = _actor->Scene->UnmanagedPointer->getMaterialFromIndex( shape->getMaterial() );
		
		this->Material = ObjectCache::GetObject<StillDesign::PhysX::Material^>( (intptr_t)material );
	}
	
	if( shape->getCCDSkeleton() != NULL )
		_ccdSkeleton = ObjectCache::GetObject<StillDesign::PhysX::CCDSkeleton^>( (intptr_t)shape->getCCDSkeleton() );
	
	ObjectCache::Add( (intptr_t)_shape, this );
}
Shape::~Shape()
{
	this->!Shape();
}
Shape::!Shape()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	_actor->UnmanagedPointer->releaseShape( *_shape );
	
	_shape = NULL;
	
	_actor = nullptr;
	_ccdSkeleton = nullptr;
	
	_material->onDisposing -= gcnew EventHandler( this, &Shape::_material_onDisposing );
	_material = nullptr;
	
	onDisposed( this, nullptr );
}
bool Shape::IsDisposed::get()
{
	return ( _shape == NULL );
}

void Shape::SaveToDescription( ShapeDescription^ shapeDescription )
{
	shapeDescription->CCDSkeleton = this->CCDSkeleton;
	shapeDescription->Material = this->Material;
}

void Shape::_material_onDisposing( System::Object^ sender, EventArgs^ e )
{
	// If the Material the Shape is Using is Deleted, Use the Default One
	this->Material = this->Actor->Scene->Materials[ 0 ];
}

RaycastHit^ Shape::Raycast( StillDesign::PhysX::Ray worldRay, float maximumDistance, RaycastBit hintFlags, bool computeHitOnly )
{
	NxRaycastHit hit;
	bool result = _shape->raycast( (NxRay)worldRay, maximumDistance, (NxU32)hintFlags, hit, computeHitOnly );
	
	if( result == true )
	{
		return (RaycastHit^)hit;
	}else{
		return nullptr;
	}
}

bool Shape::CheckOverlapsAABB( Bounds3 worldBounds )
{
	return _shape->checkOverlapAABB( (NxBounds3)worldBounds );
}
bool Shape::CheckOverlapsOBB( StillDesign::PhysX::Box worldBox )
{
	return _shape->checkOverlapOBB( (NxBox)worldBox );
}
bool Shape::CheckOverlapsSphere( Sphere sphere )
{
	return _shape->checkOverlapSphere( (NxSphere)sphere );
}
bool Shape::CheckOverlapsCapsule( Capsule capsule )
{
	return _shape->checkOverlapCapsule( (NxCapsule)capsule );
}

bool Shape::GetFlag( ShapeFlag flag )
{
	return (bool)_shape->getFlag( (NxShapeFlag)flag );
}
void Shape::SetFlag( ShapeFlag flag, bool value )
{
	_shape->setFlag( (NxShapeFlag)flag, value );
}

StillDesign::PhysX::Actor^ Shape::Actor::get()
{
	return _actor;
}
String^ Shape::Name::get()
{
	return Functions::UnmanagedToManagedString( _shape->getName() );
}
void Shape::Name::set( String^ value )
{
	_shape->setName( Functions::ManagedToUnmanagedString( value ) );
}
ShapeType Shape::Type::get()
{
	return (ShapeType)_shape->getType();
}

ShapeFlag Shape::Flags::get()
{
	unsigned int flag = 0;
	
	array<ShapeFlag>^ values = (array<ShapeFlag>^)Enum::GetValues( ShapeFlag::typeid );
	
	for each( ShapeFlag f in values )
	{
		if( this->GetFlag( f ) == true )
			flag |= (unsigned int)f;
	}
	
	return (ShapeFlag)flag;
}
void Shape::Flags::set( ShapeFlag value )
{
	array<ShapeFlag>^ values = (array<ShapeFlag>^)Enum::GetValues( ShapeFlag::typeid );
	
	for each( ShapeFlag f in values )
	{
		this->SetFlag( f, ((unsigned int)value & (unsigned int)f) != 0 );
	}
}

StillDesign::PhysX::Material^ Shape::Material::get()
{
	return _material;
}
void Shape::Material::set( StillDesign::PhysX::Material^ value )
{
	if( value == nullptr )
		throw gcnew NullReferenceException( "Cannot assign a null material" );
	
	if( _material != nullptr )
	{
		_material->onDisposing -= gcnew EventHandler( this, &Shape::_material_onDisposing );
	}
	
	_material = value;
	
	_shape->setMaterial( value->UnmanagedPointer->getMaterialIndex() );
	
	_material->onDisposing += gcnew EventHandler( this, &Shape::_material_onDisposing );
}

short Shape::Group::get()
{
	return _shape->getGroup();
}
void Shape::Group::set( short value )
{
	if( value < 0 || value >= 32 )
		throw gcnew ArgumentOutOfRangeException( "Invalid group id. Must be less than 32" );
	
	_shape->setGroup( value );
}

Bounds3 Shape::WorldSpaceBounds::get()
{
	NxBounds3 bounds;
	_shape->getWorldBounds( bounds );
	
	return (Bounds3)bounds;
}
float Shape::SkinWidth::get()
{
	return _shape->getSkinWidth();
}
void Shape::SkinWidth::set( float value )
{
	_shape->setSkinWidth( value );
}

Vector3 Shape::GlobalPosition::get()
{
	return Math::NxVec3ToVector3( _shape->getGlobalPosition() );
}
void Shape::GlobalPosition::set( Vector3 value )
{
	_shape->setGlobalPosition( Math::Vector3ToNxVec3( value ) );
}
Vector3 Shape::LocalPosition::get()
{
	return Math::NxVec3ToVector3( _shape->getLocalPosition() );
}
void Shape::LocalPosition::set( Vector3 value )
{
	_shape->setLocalPosition( Math::Vector3ToNxVec3( value ) );
}
Matrix Shape::LocalPose::get()
{
	return Math::Mat34ToMatrix( &_shape->getLocalPose() );
}
void Shape::LocalPose::set( Matrix value )
{
	_shape->setLocalPose( Math::MatrixToMat34( value ) );
}
Matrix Shape::LocalOrientation::get()
{
	return Math::Mat33ToMatrix( &_shape->getLocalOrientation() );
}
void Shape::LocalOrientation::set( Matrix value )
{
	_shape->setLocalOrientation( Math::MatrixToMat33( value ) );
}
Matrix Shape::GlobalPose::get()
{
	return Math::Mat34ToMatrix( &_shape->getGlobalPose() );
}
void Shape::GlobalPose::set( Matrix value )
{
	_shape->setGlobalPose( Math::MatrixToMat34( value ) );
}
Matrix Shape::GlobalOrientation::get()
{
	return Math::Mat33ToMatrix( &_shape->getGlobalOrientation() );
}
void Shape::GlobalOrientation::set( Matrix value )
{
	_shape->setGlobalOrientation( Math::MatrixToMat33( value ) );
}

StillDesign::PhysX::CCDSkeleton^ Shape::CCDSkeleton::get()
{
	return _ccdSkeleton;
}
void Shape::CCDSkeleton::set( StillDesign::PhysX::CCDSkeleton^ value )
{
	_ccdSkeleton = value;
	
	if( value == nullptr )
		_shape->setCCDSkeleton( NULL );
	else
		_shape->setCCDSkeleton( value->UnmanagedPointer );
}

ShapeCompartmentType Shape::NonInteractingCompartmentTypes::get()
{
	return (ShapeCompartmentType)_shape->getNonInteractingCompartmentTypes();
}
void Shape::NonInteractingCompartmentTypes::set( ShapeCompartmentType value )
{
	_shape->setNonInteractingCompartmentTypes( (NxU32)value );
}

NxShape* Shape::UnmanagedPointer::get()
{
	return _shape;
}