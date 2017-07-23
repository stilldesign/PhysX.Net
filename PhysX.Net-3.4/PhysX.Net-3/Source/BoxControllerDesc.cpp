#include "StdAfx.h"
#include "BoxControllerDesc.h"

BoxControllerDesc::BoxControllerDesc()
	: ControllerDesc(ControllerShapeType::Box)
{
	
}

PxBoxControllerDesc BoxControllerDesc::ToUnmanaged(BoxControllerDesc^ m)
{
	PxBoxControllerDesc u;
	
	ControllerDesc::AssignToUnmanaged(m, u);
	AssignToUnmanaged(m, &u);

	return u;
}
BoxControllerDesc^ BoxControllerDesc::ToManaged(PxBoxControllerDesc u)
{
	auto m = gcnew BoxControllerDesc();

	ControllerDesc::AssignToManaged(u, m);
	AssignToManaged(m, &u);

	return m;
}

void BoxControllerDesc::AssignToManaged(BoxControllerDesc^ m, PxBoxControllerDesc* u)
{
	m->HalfForwardExtent = u->halfForwardExtent;
	m->HalfHeight = u->halfHeight;
	m->HalfSideExtent = u->halfSideExtent;
}
void BoxControllerDesc::AssignToUnmanaged(BoxControllerDesc^ m, PxBoxControllerDesc* u)
{
	u->halfForwardExtent = m->HalfForwardExtent;
	u->halfHeight = m->HalfHeight;
	u->halfSideExtent = m->HalfSideExtent;
}

void BoxControllerDesc::SetToDefault()
{
	PxBoxControllerDesc d;

	ControllerDesc::AssignToManaged(d, this);
	AssignToManaged(this, &d);
}
bool BoxControllerDesc::IsValid()
{
	return ToUnmanaged(this).isValid();
}

Vector3 BoxControllerDesc::Extents::get()
{
	return Vector3(HalfSideExtent, HalfHeight, HalfForwardExtent);
}
void BoxControllerDesc::Extents::set(Vector3 value)
{
	HalfSideExtent = value.X;
	HalfHeight = value.Y;
	HalfForwardExtent = value.Z;
}