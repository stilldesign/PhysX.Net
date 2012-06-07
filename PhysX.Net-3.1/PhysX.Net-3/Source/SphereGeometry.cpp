#include "StdAfx.h"
#include "SphereGeometry.h"
#include <PxSphereGeometry.h>

using namespace PhysX;

SphereGeometry::SphereGeometry()
	: Geometry(GeometryType::Sphere)
{
	this->Radius = 0;
}
SphereGeometry::SphereGeometry(float radius)
	: Geometry(GeometryType::Sphere)
{
	this->Radius = radius;
}

PxGeometry* SphereGeometry::ToUnmanaged()
{
	return new PxSphereGeometry(this->Radius);
}