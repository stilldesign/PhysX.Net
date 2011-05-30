#include "StdAfx.h"
#include "Material.h"
#include "Physics.h"

using namespace PhysX;

Material::Material(PxMaterial* material, PhysX::Physics^ owner)
{
	if (material == NULL)
		throw gcnew ArgumentNullException("material");
	ThrowIfNullOrDisposed(owner, "owner");

	_material = material;

	ObjectTable::Add((intptr_t)_material, this, owner);
}
Material::~Material()
{
	this->!Material();
}
Material::!Material()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_material->release();
	_material = NULL;

	OnDisposed(this, nullptr);
}

bool Material::Disposed::get()
{
	return _material == NULL;
}


float Material::DynamicFriction::get()
{
	return _material->getDynamicFriction();
}
void Material::DynamicFriction::set(float value)
{
	if(value < 0.0f)
		throw gcnew ArgumentException("Dynamic friction must be greater than or equal to 0");
	
	_material->setDynamicFriction(value);
}
float Material::DynamicFrictionV::get()
{
	return _material->getDynamicFrictionV();
}
void Material::DynamicFrictionV::set(float value)
{
	_material->setDynamicFrictionV(value);
}

float Material::StaticFriction::get()
{
	return _material->getStaticFriction();
}
void Material::StaticFriction::set(float value)
{
	_material->setStaticFriction(value);
}
float Material::StaticFrictionV::get()
{
	return _material->getStaticFrictionV();
}
void Material::StaticFrictionV::set(float value)
{
	_material->setStaticFrictionV(value);
}

float Material::Restitution::get()
{
	return _material->getRestitution();
}
void Material::Restitution::set(float value)
{
	if(value < 0 || value > 1)
		throw gcnew ArgumentException("Restitution must be between 0 and 1");
	
	_material->setRestitution(value);
}

Vector3 Material::DirectionOfAnisotropy::get()
{
	return MathUtil::PxVec3ToVector3(_material->getDirOfAnisotropy());
}
void Material::DirectionOfAnisotropy::set(Vector3 value)
{
	_material->setDirOfAnisotropy(MathUtil::Vector3ToPxVec3(value));
}

MaterialFlag Material::Flags::get()
{
	return ToManagedEnum(MaterialFlag, _material->getFlags());
}
void Material::Flags::set(MaterialFlag value)
{
	_material->setFlags(ToUnmanagedEnum(PxMaterialFlag, value));
}

CombineMode Material::FrictionCombineMode::get()
{
	return ToManagedEnum(CombineMode, _material->getFrictionCombineMode());
}
void Material::FrictionCombineMode::set(CombineMode value)
{
	_material->setFrictionCombineMode(ToUnmanagedEnum(PxCombineMode, value));
}

CombineMode Material::RestitutionCombineMode::get()
{
	return (CombineMode)_material->getRestitutionCombineMode();
}
void Material::RestitutionCombineMode::set(CombineMode value)
{
	_material->setRestitutionCombineMode(ToUnmanagedEnum(PxCombineMode, value));
}

PxMaterial* Material::UnmanagedPointer::get()
{
	return _material;
}