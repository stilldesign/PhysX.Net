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
	ControllerDesc::AssignToUnmanaged(desc, &d);

	// Assign our specific properties
	d.extents = MathUtil::Vector3ToPxVec3(desc->Extents);

	return d;
}
BoxControllerDesc^ BoxControllerDesc::ToManaged(PxBoxControllerDesc desc)
{
	BoxControllerDesc^ d = gcnew BoxControllerDesc();

	// Populate the base classes properties
	ControllerDesc::AssignToManaged(&desc, d);

	// Assign our specific properties
	d->Extents = MathUtil::PxVec3ToVector3(desc.extents);

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