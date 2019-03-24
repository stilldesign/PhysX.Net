#include "StdAfx.h"
#include "BroadPhaseExt.h"
#include "Bounds3.h"

array<Bounds3>^ PhysX::BroadPhaseExt::CreateRegionsFromWorldBounds(Bounds3 globalBounds, int nbSubdiv, Nullable<int> upAxis)
{
	if (nbSubdiv <= 0)
		return array<Bounds3>::Empty<Bounds3>();

	int n = nbSubdiv*nbSubdiv;

	PxBounds3* b = (PxBounds3*)malloc(sizeof(PxBounds3) * n);

	int c = PxBroadPhaseExt::createRegionsFromWorldBounds(b, Bounds3::ToUnmanaged(globalBounds), nbSubdiv, upAxis.GetValueOrDefault(1));

	if (c <= 0)
		return array<Bounds3>::Empty<Bounds3>();

	auto m = gcnew array<Bounds3>(c);

	pin_ptr<Bounds3> pin = &m[0];
	memcpy(pin, b, sizeof(PxBounds3) * c);

	free(b);

	return m;
}