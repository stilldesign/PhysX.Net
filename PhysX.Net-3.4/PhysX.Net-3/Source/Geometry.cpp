#include "StdAfx.h"
#include "Geometry.h"

using namespace PhysX;

Geometry::Geometry(GeometryType type)
{
	this->Type = type;
}

GeometryType Geometry::Type::get()
{
	return _type;
}
void Geometry::Type::set(GeometryType value)
{
	_type = value;
}