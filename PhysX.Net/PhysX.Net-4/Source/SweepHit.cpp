#include "StdAfx.h"
#include "SweepHit.h"

PxSweepHit SweepHit::ToUnmanaged(SweepHit^ hit)
{
	PxSweepHit h;
	
	hit->PopulateUnmanaged(h);

	return h;
}
SweepHit^ SweepHit::ToManaged(PxSweepHit hit)
{
	SweepHit^ h = gcnew SweepHit();

	h->PopulateManaged(hit);

	h->HadInitialOverlap = hit.hadInitialOverlap();

	return h;
}