#include "StdAfx.h"
#include "CapsuleControllerDesc.h"

CapsuleControllerDesc::CapsuleControllerDesc()
	: ControllerDesc(ControllerShapeType::Capsule)
{
	
}

PxCapsuleControllerDesc CapsuleControllerDesc::ToUnmanaged(CapsuleControllerDesc^ m)
{
	PxCapsuleControllerDesc u;

	ControllerDesc::AssignToUnmanaged(m, u);
	AssignToUnmanaged(m, &u);

	return u;
}
CapsuleControllerDesc^ CapsuleControllerDesc::ToManaged(PxCapsuleControllerDesc u)
{
	auto m = gcnew CapsuleControllerDesc();

	ControllerDesc::AssignToManaged(u, m);
	AssignToManaged(m, &u);

	return m;
}

void CapsuleControllerDesc::AssignToManaged(CapsuleControllerDesc^ m, PxCapsuleControllerDesc* u)
{
	m->Radius = u->radius;
	m->Height = u->height;
	m->ClimbingMode = ToManagedEnum(CapsuleClimbingMode, u->climbingMode);
}
void CapsuleControllerDesc::AssignToUnmanaged(CapsuleControllerDesc^ m, PxCapsuleControllerDesc* u)
{
	u->radius = m->Radius;
	u->height = m->Height;
	u->climbingMode = ToUnmanagedEnum(PxCapsuleClimbingMode, m->ClimbingMode);
}

void CapsuleControllerDesc::SetToDefault()
{
	PxCapsuleControllerDesc d;

	ControllerDesc::AssignToManaged(d, this);
	AssignToManaged(this, &d);
}
bool CapsuleControllerDesc::IsValid()
{
	return ToUnmanaged(this).isValid();
}