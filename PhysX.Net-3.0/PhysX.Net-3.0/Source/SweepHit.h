#pragma once

#include "SceneQueryImpactHit.h"

namespace PhysX
{
	/// <summary>
	/// This structure captures results for a single sweep query.
	/// </summary>
	public ref class SweepHit : SceneQueryImpactHit
	{
		internal:
			static PxSweepHit ToUnmanaged(SweepHit^ hit);
			static SweepHit^ ToManaged(PxSweepHit hit);

		public:
			/// <summary>
			/// Only valid when using BatchQuery.LinearCompoundGeometrySweepSingle() or Scene.SweepAny/Single/Multiple() with
			/// compound of geometry objects. Index of the geometry object that hits the HitObject.
			/// </summary>
			property int SweepGeometryIndex;
	};
};