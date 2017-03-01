#include "StdAfx.h"
#include "SimpleContact.h"

void SimpleContact::PopulateManaged(SimpleContact^ managed, PxContact* unmanaged)
{
	managed->Contact = MathUtil::PxVec3ToVector3(unmanaged->contact);
	managed->Separation = unmanaged->separation;
}
void SimpleContact::PopulateUnmanaged(SimpleContact^ managed, PxContact* unmanaged)
{
	unmanaged->contact = MathUtil::Vector3ToPxVec3(managed->Contact);
	unmanaged->separation = managed->Separation;
}