#include "StdAfx.h"
#include "SphereGeometry.h"

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
SphereGeometry::SphereGeometry(PxSphereGeometry geom)
	: Geometry(GeometryType::Sphere)
{
	this->Radius = geom.radius;
}

PxGeometry* SphereGeometry::ToUnmanaged()
{
	return new PxSphereGeometry(this->Radius);
}
SphereGeometry^ SphereGeometry::ToManaged(PxSphereGeometry sphere)
{
	return gcnew SphereGeometry(sphere.radius);
}