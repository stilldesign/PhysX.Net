#include "StdAfx.h"
#include "Material.h"
#include "Physics.h"
#include "Serializable.h"

using namespace PhysX;

Material::Material(PxMaterial* material, PhysX::Physics^ owner)
{
	if (material == NULL)
		throw gcnew ArgumentNullException("material");
	ThrowIfNullOrDisposed(owner, "owner");

	_material = material;

	ObjectTable::Instance->Add((intptr_t)_material, this, owner);
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
	return (_material == NULL);
}

Serializable^ Material::AsSerializable()
{
	return gcnew Serializable(_material);
}

String^ Material::ToString()
{
	return String::Format("Material. Dynamic Friction: {0:0.0#} Static Friction: {1:0.0#} Restitution: {2:0.0#}", DynamicFriction, StaticFriction, Restitution);
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

float Material::StaticFriction::get()
{
	return _material->getStaticFriction();
}
void Material::StaticFriction::set(float value)
{
	_material->setStaticFriction(value);
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

MaterialFlags Material::Flags::get()
{
	return ToManagedEnum(MaterialFlags, _material->getFlags());
}
void Material::Flags::set(MaterialFlags value)
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

String^ Material::ConcreteTypeName::get()
{
	return Util::ToManagedString(_material->getConcreteTypeName());
}

PxMaterial* Material::UnmanagedPointer::get()
{
	return _material;
}