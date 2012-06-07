#include "StdAfx.h"
#include "BoxControllerDesc.h"

BoxControllerDesc::BoxControllerDesc()
	: ControllerDesc(ControllerShapeType::Box)
{
	
}

PxBoxControllerDesc BoxControllerDesc::ToUnmanaged(BoxControllerDesc^ desc)
{
	PxBoxControllerDesc d;
	
	// Populate the base classes properties
	ControllerDesc::AssignToUnmanaged(desc, d);

	// Assign our specific properties
	d.halfForwardExtent = desc->HalfForwardExtent;
	d.halfHeight = desc->HalfHeight;
	d.halfSideExtent = desc->HalfSideExtent;

	return d;
}
BoxControllerDesc^ BoxControllerDesc::ToManaged(PxBoxControllerDesc desc)
{
	BoxControllerDesc^ d = gcnew BoxControllerDesc();

	// Populate the base classes properties
	ControllerDesc::AssignToManaged(desc, d);

	// Assign our specific properties
	d->HalfForwardExtent = desc.halfForwardExtent;
	d->HalfHeight = desc.halfHeight;
	d->HalfSideExtent = desc.halfSideExtent;

	return d;
}

PxControllerDesc BoxControllerDesc::ToUnmanaged()
{
	return BoxControllerDesc::ToUnmanaged(this);
}

void BoxControllerDesc::SetToDefault()
{
	
}
bool BoxControllerDesc::IsValid()
{
	auto d = ToUnmanaged(this);

	return d.isValid();
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