#include "StdAfx.h"
#include "ExtendedContact.h"

PxExtendedContact* ExtendedContact::ToUnmanaged(ExtendedContact^ managed)
{
	auto unmanaged = new PxExtendedContact();

	PopulateUnmanaged(managed, unmanaged);

	return unmanaged;
}
ExtendedContact^ ExtendedContact::ToManaged(PxExtendedContact* unmanaged)
{
	auto p = gcnew ExtendedContact();
	p->MaxImpulse = unmanaged->maxImpulse;
	p->TargetVelocity = MathUtil::PxVec3ToVector3(unmanaged->targetVelocity);

	SimpleContact::PopulateManaged(p, unmanaged);

	return p;
}

void ExtendedContact::PopulateUnmanaged(ExtendedContact^ managed, PxExtendedContact* unmanaged)
{
	SimpleContact::PopulateUnmanaged(managed, unmanaged);

	unmanaged->targetVelocity = MathUtil::Vector3ToPxVec3(managed->TargetVelocity);
	unmanaged->maxImpulse = managed->MaxImpulse;
}