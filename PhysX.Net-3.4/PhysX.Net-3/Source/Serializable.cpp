#include "StdAfx.h"
#include "Serializable.h"

Serializable::Serializable(PxBase* serializable)
{
	_serializable = serializable;
}
Serializable::~Serializable()
{
	this->!Serializable();
}
Serializable::!Serializable()
{
	_serializable = NULL;
}

String^ Serializable::ConcreteTypeName::get()
{
	return Util::ToManagedString(_serializable->getConcreteTypeName());
}

PhysX::ConcreteType Serializable::ConcreteType::get()
{
	return ToManagedEnum(PhysX::ConcreteType, _serializable->getConcreteType());
}