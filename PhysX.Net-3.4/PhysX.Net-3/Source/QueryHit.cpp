#include "StdAfx.h"
#include "QueryHit.h"
#include "ActorShape.h"

void QueryHit::PopulateUnmanaged(PxQueryHit& hit)
{
	ActorShape::PopulateUnmanaged(hit);

	hit.faceIndex = this->FaceIndex;
}
void QueryHit::PopulateManaged(PxQueryHit hit)
{
	ActorShape::PopulateManaged(hit);

	this->FaceIndex = hit.faceIndex;
}

QueryHit^ QueryHit::ToManaged(PxQueryHit* hit)
{
	if (hit == NULL)
		throw gcnew ArgumentNullException("hit");

	auto h = gcnew QueryHit();
	
	h->PopulateManaged(*hit);

	return h;
}