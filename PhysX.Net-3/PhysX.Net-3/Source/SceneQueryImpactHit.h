#pragma once

#include "SceneQueryHit.h"

namespace PhysX
{
	/// <summary>
	/// Scene query hit information for queries with impacts.
	/// SceneQueryFlag flags can be passed to scene query functions, as an optimization, to cause the SDK to only generate specific members of this structure.
	/// </summary>
	public ref class SceneQueryImpactHit : SceneQueryHit
	{
		internal:
			void PopulateUnmanaged(PxSceneQueryImpactHit& hit);
			void PopulateManaged(PxSceneQueryImpactHit& hit);

		public:
			/// <summary>
			/// World-space impact point (flag: SceneQueryFlag.Impact).
			/// </summary>
			property Vector3 Impact;

			/// <summary>
			/// World-space impact normal (flag: SceneQueryFlag.Normal).
			/// </summary>
			property Vector3 Normal;

			/// <summary>
			/// Distance to hit (flag: SceneQueryFlag.Distance).
			/// </summary>
			property float Distance;
	};
};