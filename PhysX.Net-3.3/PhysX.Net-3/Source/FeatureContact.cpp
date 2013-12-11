#include "StdAfx.h"
#include "FeatureContact.h"

PxFeatureContact FeatureContact::ToUnmanaged(FeatureContact^ managed)
{
	PxFeatureContact unmanaged;

	PopulateUnmanaged(managed, unmanaged);

	return unmanaged;
}
FeatureContact^ FeatureContact::ToManaged(PxFeatureContact point)
{
	auto p = gcnew FeatureContact();
		p->Separation = point.separation;
		p->InternalFaceIndex0 = point.internalFaceIndex0;
		p->InternalFaceIndex1 = point.internalFaceIndex1;

	return p;
}

void FeatureContact::PopulateUnmanaged(FeatureContact^ managed, PxFeatureContact& unmanaged)
{
	SimpleContact::PopulateUnmanaged(managed, unmanaged);

	unmanaged.separation = managed->Separation;
	unmanaged.internalFaceIndex0 = managed->InternalFaceIndex0;
	unmanaged.internalFaceIndex1 = managed->InternalFaceIndex1;
}