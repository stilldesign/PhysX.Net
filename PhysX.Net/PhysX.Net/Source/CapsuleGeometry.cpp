#include "StdAfx.h"
#include "CapsuleGeometry.h"

using namespace PhysX;

CapsuleGeometry::CapsuleGeometry()
	: Geometry(GeometryType::Sphere)
{
	this->Radius = 0;
}
CapsuleGeometry::CapsuleGeometry(float radius, float halfHeight)
	: Geometry(GeometryType::Capsule)
{
	this->Radius = radius;
	this->HalfHeight = halfHeight;
}

PxGeometry* CapsuleGeometry::ToUnmanaged()
{
	return new PxCapsuleGeometry(this->Radius, this->HalfHeight);
}

CapsuleGeometry^ CapsuleGeometry::ToManaged(PxCapsuleGeometry capsule)
{
	return gcnew CapsuleGeometry(capsule.radius, capsule.halfHeight);
}