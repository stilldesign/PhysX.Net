#include "StdAfx.h"
#include "RaycastHit.h"

PxRaycastHit RaycastHit::ToUnmanaged(RaycastHit^ hit)
{
	PxRaycastHit h;
		h.u = hit->U;
		h.v = hit->V;

	return h;
}
RaycastHit^ RaycastHit::ToManaged(PxRaycastHit& hit)
{
	RaycastHit^ h = gcnew RaycastHit();

	h->PopulateManaged(hit);

	h->U = hit.u;
	h->V = hit.v;

	return h;
}