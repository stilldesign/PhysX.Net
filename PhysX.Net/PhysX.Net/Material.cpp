#include "StdAfx.h"

#include "Material.h"
#include "Scene.h"
#include "Material Description.h"
#include "Functions.h"

#include <NxMaterial.h>
#include <NxMaterialDesc.h>
#include <NxScene.h> 

using namespace StillDesign::PhysX;

Material::Material( NxMaterial* material )
{
	Debug::Assert( material != NULL );
	
	ObjectCache::Add( (intptr_t)material, this );
	
	_material = material;
	
	_scene = ObjectCache::GetObject<StillDesign::PhysX::Scene^>( (intptr_t)(&material->getScene()) );
}
Material::~Material()
{
	this->!Material();
}
Material::!Material()
{
	if( this->IsDisposed == true || this->Index == 0 )
		return;
	
	onDisposing( this, nullptr );
	
	NxScene* scene = &_material->getScene();
	scene->releaseMaterial( *_material );
	
	_material = NULL;
	
	_scene = nullptr;
	
	onDisposed( this, nullptr );
}
bool Material::IsDisposed::get()
{
	return ( _material == NULL );
}

MaterialDescription^ Material::SaveToDescription()
{
	MaterialDescription^ desc = gcnew MaterialDescription();
	
	_material->saveToDesc( *desc->UnmanagedPointer );
	
	desc->Name = this->Name;
	
	return desc;
}
void Material::LoadFromDescription( MaterialDescription^ description )
{
	if( description == nullptr )
		throw gcnew ArgumentNullException( "description" );
	
	_material->loadFromDesc( *description->UnmanagedPointer );
	
	this->Name = description->Name;
}

StillDesign::PhysX::Scene^ Material::Scene::get()
{
	return _scene;
}
int Material::Index::get()
{
	return _material->getMaterialIndex();
}

String^ Material::Name::get()
{
	return _name;
}
void Material::Name::set( String^ value )
{
	_name = value;
}

float Material::DynamicFriction::get()
{
	return _material->getDynamicFriction();
}
void Material::DynamicFriction::set( float value )
{
	if( value < 0.0f )
		throw gcnew ArgumentException( "Dynamic friction must be greater than or equal to 0" );
	
	_material->setDynamicFriction( value );
}
float Material::DynamicFrictionV::get()
{
	return _material->getDynamicFrictionV();
}
void Material::DynamicFrictionV::set( float value )
{
	_material->setDynamicFrictionV( value );
}

float Material::StaticFriction::get()
{
	return _material->getStaticFriction();
}
void Material::StaticFriction::set( float value )
{
	_material->setStaticFriction( value );
}
float Material::StaticFrictionV::get()
{
	return _material->getStaticFrictionV();
}
void Material::StaticFrictionV::set( float value )
{
	_material->setStaticFrictionV( value );
}

float Material::Restitution::get()
{
	return _material->getRestitution();
}
void Material::Restitution::set( float value )
{
	if( value < 0 || value > 1 )
		throw gcnew ArgumentException( "Restitution must be between 0 and 1" );
	
	_material->setRestitution( value );
}

Vector3 Material::DirectionOfAnisotropy::get()
{
	return Math::NxVec3ToVector3( _material->getDirOfAnisotropy() );
}
void Material::DirectionOfAnisotropy::set( Vector3 value )
{
	_material->setDirOfAnisotropy( Math::Vector3ToNxVec3( value ) );
}

MaterialFlag Material::Flags::get()
{
	return (MaterialFlag)_material->getFlags();
}
void Material::Flags::set( MaterialFlag value )
{
	_material->setFlags( (unsigned int)value );
}

CombineMode Material::FrictionCombineMode::get()
{
	return (CombineMode)_material->getFrictionCombineMode();
}
void Material::FrictionCombineMode::set( CombineMode value )
{
	_material->setFrictionCombineMode( (NxCombineMode)value );
}

CombineMode Material::RestitutionCombineMode::get()
{
	return (CombineMode)_material->getRestitutionCombineMode();
}
void Material::RestitutionCombineMode::set( CombineMode value )
{
	_material->setRestitutionCombineMode( (NxCombineMode)value );
}

Object^ Material::UserData::get()
{
	return _userData;
}
void Material::UserData::set( Object^ value )
{
	_userData = value;
}

NxMaterial* Material::UnmanagedPointer::get()
{
	return _material;
}