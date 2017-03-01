#include "StdAfx.h"
#include "ConstraintDominance.h"

ConstraintDominance::ConstraintDominance(float dominance0, float dominance1)
{
	Dominance0 = dominance0;
	Dominance1 = dominance1;
}

ConstraintDominance ConstraintDominance::ToManaged(PxConstraintDominance constraintDominance)
{
	return ConstraintDominance(constraintDominance.dominance0, constraintDominance.dominance1);
}

PxConstraintDominance ConstraintDominance::ToUnmanaged(ConstraintDominance constraintDominance)
{
	return PxConstraintDominance(constraintDominance.Dominance0, constraintDominance.Dominance1);
}