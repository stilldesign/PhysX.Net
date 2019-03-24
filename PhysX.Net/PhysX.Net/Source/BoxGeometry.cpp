#include "StdAfx.h"
#include "BoxGeometry.h"

BoxGeometry::BoxGeometry()
	: Geometry(GeometryType::Box)
{
	this->HalfExtents = Vector3::Zero;
}
BoxGeometry::BoxGeometry(float hX, float hY, float hZ)
	: Geometry(GeometryType::Box)
{
	this->HalfExtents = Vector3(hX, hY, hZ);
}
BoxGeometry::BoxGeometry(Vector3 halfExtents)
	: Geometry(GeometryType::Box)
{
	this->HalfExtents = halfExtents;
}

BoxGeometry^ BoxGeometry::ToManaged(PxBoxGeometry box)
{
	return gcnew BoxGeometry(box.halfExtents.x, box.halfExtents.y, box.halfExtents.z);
}

//

Vector3 BoxGeometry::Size::get()
{
	return this->HalfExtents * 2;
}
void BoxGeometry::Size::set(Vector3 value)
{
	this->HalfExtents = value * 0.5f;
}

PxGeometry* BoxGeometry::ToUnmanaged()
{
	PxVec3 v = UV(this->HalfExtents);

	return new PxBoxGeometry(v);
}