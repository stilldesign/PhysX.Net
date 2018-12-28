#pragma once

#include "Geometry.h"
#include "SceneEnum.h"
#include "Bounds3.h"

namespace PhysX
{
	ref class SweepHit;

	public ref class GeometryQuery
	{
	public:
		static SweepHit^ Sweep(Vector3 unitDirection, float distance, Geometry^ geom0, Matrix pose0, Geometry^ geom1, Matrix pose1, [Optional] Nullable<HitFlag> hitFlags, [Optional] Nullable<float> inflation);

		// TODO: Overlap
		// TODO: Raycast
		// TODO: ComputePenetration
		// TODO: PointDistance

		static Bounds3 GetWorldBounds(Geometry^ geometry, Matrix pose, [Optional] Nullable<float> inflation);
	};
}