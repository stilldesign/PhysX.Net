#include "StdAfx.h"
#include "TolerancesScale.h"

using namespace PhysX;

PxTolerancesScale TolerancesScale::ToUnmanaged(TolerancesScale scale)
{
	PxTolerancesScale s;
		s.length = scale.Length;
		s.mass = scale.Mass;
		s.speed = scale.Speed;

	return s;
}
TolerancesScale TolerancesScale::ToManaged(PxTolerancesScale scale)
{
	TolerancesScale s;
		s.Length = scale.length;
		s.Mass = scale.mass;
		s.Speed = scale.speed;

	return s;
}