#include "StdAfx.h"
#include "RaycastHit.h"

PxRaycastHit RaycastHit::ToUnmanaged(RaycastHit^ hit)
{
	PxRaycastHit h;
		h.u = hit->U;
		h.v = hit->V;

	((LocationHit^)hit)->PopulateUnmanaged(h);

	return h;
}
RaycastHit^ RaycastHit::ToManaged(PxRaycastHit& hit)
{
	RaycastHit^ h = gcnew RaycastHit();
		h->U = hit.u;
		h->V = hit.v;

	((LocationHit^)h)->PopulateManaged(hit);

	return h;
}