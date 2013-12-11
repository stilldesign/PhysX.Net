#include "StdAfx.h"
#include "InternalRaycastCallback.h"
#include "RaycastHit.h"

InternalRaycastCallback::InternalRaycastCallback(PxRaycastHit *aTouches, PxU32 aMaxNbTouches)
	: PxHitCallback<PxRaycastHit>(aTouches, aMaxNbTouches)
{

}

PxAgain InternalRaycastCallback::processTouches(const PxRaycastHit* buffer, PxU32 nbHits)
{
	auto managedHits = gcnew array<RaycastHit^>(nbHits);

	for (unsigned int i = 0; i < nbHits; i++)
	{
		auto hit = RaycastHit::ToManaged((PxRaycastHit)buffer[i]);

		managedHits[i] = hit;
	}

	bool again = _managedCallback->Invoke(managedHits);

	return again;
}