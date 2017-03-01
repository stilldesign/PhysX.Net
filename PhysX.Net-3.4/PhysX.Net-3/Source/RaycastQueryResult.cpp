#include "StdAfx.h"
#include "RaycastQueryResult.h"
#include "RaycastHit.h"

RaycastQueryResult^ RaycastQueryResult::ToManaged(PxRaycastQueryResult result)
{
	RaycastQueryResult^ hit = gcnew RaycastQueryResult();
	
	auto touches = gcnew array<RaycastHit^>(result.nbTouches);

	for (unsigned int i = 0; i < result.nbTouches; i++)
	{
		PxRaycastHit h = result.touches[i];

		touches[i] = RaycastHit::ToManaged(h);
	}

	hit->Touches = touches;
	hit->QueryStatus = (BatchQueryStatus)result.queryStatus;

	return hit;
}

PxRaycastQueryResult RaycastQueryResult::ToUnmanaged(RaycastQueryResult^ result)
{
	ThrowIfNull(result, "result");

	PxRaycastQueryResult hit;
	
	PxRaycastHit* touches = new PxRaycastHit[result->Touches->Length];

	for (int i = 0; i < result->Touches->Length; i++)
	{
		RaycastHit^ t = result->Touches[i];

		touches[i] = RaycastHit::ToUnmanaged(t);
	}

	hit.touches = touches;
	hit.queryStatus = (PxU8)result->QueryStatus;

	return hit;
}