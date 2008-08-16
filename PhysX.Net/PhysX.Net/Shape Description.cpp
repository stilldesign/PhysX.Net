#include "StdAfx.h"

#include "Shape Description.h"
#include "Scene.h"
#include "Material.h"
#include "Functions.h"
#include "Math.h"
#include "CCD Skeleton.h"

using namespace StillDesign::PhysX;

ShapeDescription::ShapeDescription( NxShapeDesc* description )
{
	Debug::Assert( description != NULL );
	
	_desc = description;
}
ShapeDescription::~ShapeDescription()
{
	this->!ShapeDescription();
}
ShapeDescription::!ShapeDescription()
{
	SAFE_DELETE( _desc );
}

String^ ShapeDescription::Name::get()
{
	return Functions::UnmanagedToManagedString( _desc->name );
}
void ShapeDescription::Name::set( String^ value )
{
	_desc->name = Functions::ManagedToUnmanagedString( value );
}

Matrix ShapeDescription::LocalPose::get()
{
	return Math::Mat34ToMatrix( &_desc->localPose );
}
void ShapeDescription::LocalPose::set( Matrix value )
{
	_desc->localPose = Math::MatrixToMat34( value );
}

Vector3 ShapeDescription::LocalPosition::get()
{
	return Math::NxVec3ToVector3( _desc->localPose.t );
}
void ShapeDescription::LocalPosition::set( Vector3 value )
{
	_desc->localPose.t = Math::Vector3ToNxVec3( value );
}
Matrix ShapeDescription::LocalRotation::get()
{
	return Math::Mat33ToMatrix( &_desc->localPose.M );
}
void ShapeDescription::LocalRotation::set( Matrix value )
{
	_desc->localPose.M = Math::MatrixToMat33( value );
}

DescriptorValidity^ ShapeDescription::IsValid()
{
	if(!_desc->localPose.isFinite())
		return DescriptorValidity::Invalid( "!localPose.isFinite()" );
		
	if(_desc->group>=32)
		return DescriptorValidity::Invalid( "group>=32" );
		
	if(_desc->getType() >= NX_SHAPE_COUNT)
		return DescriptorValidity::Invalid( "type >= NX_SHAPE_COUNT" );
		
	if(_desc->materialIndex==0xffff)
		return DescriptorValidity::Invalid( "materialIndex==0xffff" );	// 0xffff is reserved for internal usage
		
	if (_desc->skinWidth != -1 && _desc->skinWidth < 0)
		return DescriptorValidity::Invalid( "skinWidth != -1 && skinWidth < 0" );
	
	return _desc->isValid();
}
void ShapeDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_material = nullptr;
	_ccdSkeleton = nullptr;
}

ShapeType ShapeDescription::Type::get()
{
	return (ShapeType)_desc->getType();
}

// Material
StillDesign::PhysX::Material^ ShapeDescription::Material::get()
{
	return _material;
}
void ShapeDescription::Material::set( StillDesign::PhysX::Material^ value )
{
	ThrowIfNull( value, "value" );
	
	_material = value;
	
	_desc->materialIndex = value->Index;
}

StillDesign::PhysX::CCDSkeleton^ ShapeDescription::CCDSkeleton::get()
{
	return _ccdSkeleton;
}
void ShapeDescription::CCDSkeleton::set( StillDesign::PhysX::CCDSkeleton^ value )
{
	_ccdSkeleton = value;
	
	if( value != nullptr )
		_desc->ccdSkeleton = value->UnmanagedPointer;
	else
		_desc->ccdSkeleton = NULL;
}

// Density
float ShapeDescription::Density::get()
{
	return _desc->density;
}
void ShapeDescription::Density::set( float value )
{
	_desc->density = value;
}

// Mass
float ShapeDescription::Mass::get()
{
	return _desc->mass;
}
void ShapeDescription::Mass::set( float value )
{
	_desc->mass = value;
}
float ShapeDescription::SkinWidth::get()
{
	return _desc->skinWidth;
}
void ShapeDescription::SkinWidth::set( float value )
{
	_desc->skinWidth = value;
}

StillDesign::PhysX::GroupsMask ShapeDescription::GroupsMask::get()
{
	return (StillDesign::PhysX::GroupsMask)_desc->groupsMask;
}
void ShapeDescription::GroupsMask::set( StillDesign::PhysX::GroupsMask value )
{
	_desc->groupsMask = (NxGroupsMask)value;
}

// Shape
StillDesign::PhysX::ShapeFlag ShapeDescription::Flags::get()
{
	return (StillDesign::PhysX::ShapeFlag)_desc->shapeFlags;
}
void ShapeDescription::Flags::set( StillDesign::PhysX::ShapeFlag value )
{
	_desc->shapeFlags = (NxU32)value;
}

ShapeCompartmentType ShapeDescription::NonInteractingCompartmentTypes::get()
{
	return (ShapeCompartmentType)_desc->nonInteractingCompartmentTypes;
}
void ShapeDescription::NonInteractingCompartmentTypes::set( ShapeCompartmentType value )
{
	_desc->nonInteractingCompartmentTypes = (NxU32)value;
}

NxShapeDesc* ShapeDescription::UnmanagedPointer::get()
{
	return _desc;
}