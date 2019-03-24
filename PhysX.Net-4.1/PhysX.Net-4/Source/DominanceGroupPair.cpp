#include "StdAfx.h"
#include "DominanceGroupPair.h"

DominanceGroupPair::DominanceGroupPair(float dominance0, float dominance1)
{
	Dominance0 = dominance0;
	Dominance1 = dominance1;
}

DominanceGroupPair DominanceGroupPair::ToManaged(PxDominanceGroupPair constraintDominance)
{
	return DominanceGroupPair(constraintDominance.dominance0, constraintDominance.dominance1);
}

PxDominanceGroupPair DominanceGroupPair::ToUnmanaged(DominanceGroupPair constraintDominance)
{
	return PxDominanceGroupPair(constraintDominance.Dominance0, constraintDominance.Dominance1);
}