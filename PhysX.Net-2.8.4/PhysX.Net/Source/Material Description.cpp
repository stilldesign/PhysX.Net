#include "StdAfx.h"

#include "Spring Description.h"
#include "Material Enums.h"

#include "Material Description.h"

using namespace StillDesign::PhysX;

MaterialDescription::MaterialDescription()
{
	_desc = new NxMaterialDesc();
}
MaterialDescription::MaterialDescription( NxMaterialDesc* desc )
{
	_desc = desc;
}
MaterialDescription::~MaterialDescription()
{
	this->!MaterialDescription();
}
MaterialDescription::!MaterialDescription()
{
	SAFE_DELETE( _desc );
}

bool MaterialDescription::IsValid()
{
	return _desc->isValid();
}
int MaterialDescription::CheckValid()
{
	return _desc->checkValid();
}
void MaterialDescription::SetToDefault()
{
	_desc->setToDefault();
	
	_name = nullptr;
}

String^ MaterialDescription::Name::get()
{
	return _name;
}
void MaterialDescription::Name::set( String^ value )
{
	_name = value;
}

float MaterialDescription::DynamicFriction::get()
{
	return _desc->dynamicFriction;
}
void MaterialDescription::DynamicFriction::set( float value )
{
	_desc->dynamicFriction = value;
}

float MaterialDescription::StaticFriction::get()
{
	return _desc->staticFriction;
}
void MaterialDescription::StaticFriction::set( float value )
{
	_desc->staticFriction = value;
}

float MaterialDescription::DynamicFrictionV::get()
{
	return _desc->dynamicFrictionV;
}
void MaterialDescription::DynamicFrictionV::set( float value )
{
	_desc->dynamicFrictionV = value;
}

float MaterialDescription::StaticFrictionV::get()
{
	return _desc->staticFrictionV;
}
void MaterialDescription::StaticFrictionV::set( float value )
{
	_desc->staticFrictionV = value;
}

float MaterialDescription::Restitution::get()
{
	return _desc->restitution;
}
void MaterialDescription::Restitution::set( float value )
{
	_desc->restitution = value;
}

Vector3 MaterialDescription::DirectionOfAnisotropy::get()
{
	return Vector3( _desc->dirOfAnisotropy.x, _desc->dirOfAnisotropy.y, _desc->dirOfAnisotropy.z );
}
void MaterialDescription::DirectionOfAnisotropy::set( Vector3 value )
{
	_desc->dirOfAnisotropy = NxVec3( value.X, value.Y, value.Z );
}

MaterialFlag MaterialDescription::Flags::get()
{
	return (MaterialFlag)_desc->flags;
}
void MaterialDescription::Flags::set( MaterialFlag value )
{
	_desc->flags = (NxU32)value;
}

CombineMode MaterialDescription::FrictionCombineMode::get()
{
	return (CombineMode)_desc->frictionCombineMode;
}
void MaterialDescription::FrictionCombineMode::set( CombineMode value )
{
	_desc->frictionCombineMode = (NxCombineMode)value;
}

CombineMode MaterialDescription::RestitutionCombineMode::get()
{
	return (CombineMode)_desc->restitutionCombineMode;
}
void MaterialDescription::RestitutionCombineMode::set( CombineMode value )
{
	_desc->restitutionCombineMode = (NxCombineMode)value;
}

NxMaterialDesc* MaterialDescription::UnmanagedPointer::get()
{
	return _desc;
}