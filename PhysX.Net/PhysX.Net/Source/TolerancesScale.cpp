#include "StdAfx.h"
#include "TolerancesScale.h"

using namespace PhysX;

PxTolerancesScale TolerancesScale::ToUnmanaged(TolerancesScale scale)
{
	PxTolerancesScale s;
		s.length = scale.Length;
		s.speed = scale.Speed;

	return s;
}
TolerancesScale TolerancesScale::ToManaged(PxTolerancesScale scale)
{
	TolerancesScale s;
		s.Length = scale.length;
		s.Speed = scale.speed;

	return s;
}

TolerancesScale TolerancesScale::Default::get()
{
	return ToManaged(PxTolerancesScale());
}