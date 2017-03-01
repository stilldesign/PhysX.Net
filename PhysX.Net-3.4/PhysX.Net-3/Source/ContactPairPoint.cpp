#include "StdAfx.h"
#include "ContactPairPoint.h"

ContactPairPoint^ ContactPairPoint::ToManaged(PxContactPairPoint unmanaged)
{
	auto managed = gcnew ContactPairPoint();

	managed->Position = MV(unmanaged.position);
	managed->Separation = unmanaged.separation;
	managed->Normal = MV(unmanaged.normal);
	managed->InternalFaceIndex0 = unmanaged.internalFaceIndex0;
	managed->InternalFaceIndex1 = unmanaged.internalFaceIndex1;
	managed->Impulse = MV(unmanaged.impulse);

	return managed;
}