#include "StdAfx.h"
#include "RaycastQueryResult.h"
#include "RaycastHit.h"

RaycastQueryResult^ RaycastQueryResult::ToManaged(PxRaycastQueryResult result)
{
	RaycastQueryResult^ hit = gcnew RaycastQueryResult();
	
	auto hits = gcnew array<RaycastHit^>(result.nbHits);

	for (int i = 0; i < result.nbHits; i++)
	{
		PxRaycastHit h = result.hits[i];

		hits[i] = RaycastHit::ToManaged(h);
	}

	hit->Hits = hits;
	hit->QueryStatus = result.queryStatus;

	return hit;
}

PxRaycastQueryResult RaycastQueryResult::ToUnmanaged(RaycastQueryResult^ result)
{
	PxRaycastQueryResult hit;
	
	PxRaycastHit* hits = new PxRaycastHit[result->Hits->Length];

	for (int i = 0; i < result->Hits->Length; i++)
	{
		RaycastHit^ h = result->Hits[i];

		hits[i] = RaycastHit::ToUnmanaged(h);
	}

	hit.hits = hits;
	hit.queryStatus = result->QueryStatus;

	return hit;
}