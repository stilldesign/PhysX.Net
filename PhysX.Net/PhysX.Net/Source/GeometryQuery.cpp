#include "StdAfx.h"
#include "GeometryQuery.h"
#include "SweepHit.h"

SweepHit^ GeometryQuery::Sweep(Vector3 unitDirection, float distance, Geometry^ geom0, Matrix pose0, Geometry^ geom1, Matrix pose1, [Optional] Nullable<HitFlag> hitFlags, [Optional] Nullable<float> inflation)
{
	if (geom0 == nullptr)
		throw gcnew ArgumentNullException("geom0");
	if (geom1 == nullptr)
		throw gcnew ArgumentNullException("geom1");

	PxSweepHit sh;

	PxGeometry* g0 = geom0->ToUnmanaged();
	PxGeometry* g1 = geom1->ToUnmanaged();

	bool result = PxGeometryQuery::sweep
	(
		UV(unitDirection),
		distance,
		*g0,
		UM(pose0),
		*g1,
		UM(pose1),
		sh,
		ToUnmanagedEnum(PxHitFlag, hitFlags.GetValueOrDefault(HitFlag::Default)),
		inflation.GetValueOrDefault(0)
	);

	delete g0, g1;

	if (!result)
		return nullptr;

	return SweepHit::ToManaged(sh);
}

Bounds3 GeometryQuery::GetWorldBounds(Geometry^ geometry, Matrix pose, [Optional] Nullable<float> inflation)
{
	if (geometry == nullptr)
		throw gcnew ArgumentNullException("geometry");

	PxGeometry* g = geometry->ToUnmanaged();

	PxTransform t = UM(pose);

	PxBounds3 bounds = PxGeometryQuery::getWorldBounds
	(
		*g,
		t,
		inflation.GetValueOrDefault(1.01f)
	);

	delete g;

	return Bounds3::ToManaged(bounds);
}