#include "StdAfx.h"
#include "SimpleContact.h"

void SimpleContact::PopulateUnmanaged(SimpleContact^ managed, PxSimpleContact& unmanaged)
{
	unmanaged.contact = MathUtil::Vector3ToPxVec3(managed->Contact);
	unmanaged.separation = managed->Separation;
}