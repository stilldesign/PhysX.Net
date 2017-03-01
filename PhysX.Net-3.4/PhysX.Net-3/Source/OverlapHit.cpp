#include "StdAfx.h"
#include "OverlapHit.h"

PxOverlapHit OverlapHit::ToUnmanaged(OverlapHit^ hit)
{
	PxOverlapHit h;

	((LocationHit^)hit)->PopulateUnmanaged(h);

	return h;
}
OverlapHit^ OverlapHit::ToManaged(PxOverlapHit& hit)
{
	auto h = gcnew OverlapHit();

	((LocationHit^)h)->PopulateManaged(hit);

	return h;
}