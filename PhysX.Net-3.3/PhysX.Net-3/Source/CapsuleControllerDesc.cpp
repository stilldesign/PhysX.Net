#include "StdAfx.h"
#include "CapsuleControllerDesc.h"

CapsuleControllerDesc::CapsuleControllerDesc()
	: ControllerDesc(ControllerShapeType::Capsule)
{
	
}

PxCapsuleControllerDesc CapsuleControllerDesc::ToUnmanaged(CapsuleControllerDesc^ desc)
{
	PxCapsuleControllerDesc d;

	// Populate the base classes properties
	ControllerDesc::AssignToUnmanaged(desc, d);

	// Assign our specific properties
	d.radius = desc->Radius;
	d.height = desc->Height;
	d.climbingMode = ToUnmanagedEnum(PxCapsuleClimbingMode, desc->ClimbingMode);

	return d;
}
CapsuleControllerDesc^ CapsuleControllerDesc::ToManaged(PxCapsuleControllerDesc desc)
{
	CapsuleControllerDesc^ d = gcnew CapsuleControllerDesc();

	// Populate the base classes properties
	ControllerDesc::AssignToManaged(desc, d);

	// Assign our specific properties
	d->Radius = desc.radius;
	d->Height = desc.height;
	d->ClimbingMode = ToManagedEnum(CapsuleClimbingMode, desc.climbingMode);

	return d;
}

PxCapsuleControllerDesc CapsuleControllerDesc::ToUnmanaged()
{
	return CapsuleControllerDesc::ToUnmanaged(this);
}

void CapsuleControllerDesc::SetToDefault()
{
	ControllerDesc::SetToDefault();

	// Values from PxCapsuleControllerDesc::setToDefault()
	Radius = 0;
	Height = 0;
	ClimbingMode = CapsuleClimbingMode::Easy;
}
bool CapsuleControllerDesc::IsValid()
{
	auto desc = ToUnmanaged(this);

	return desc.isValid();
}