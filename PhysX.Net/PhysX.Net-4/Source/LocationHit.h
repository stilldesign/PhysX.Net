#pragma once

#include "QueryHit.h"

namespace PhysX
{
	/// <summary>
	/// Scene query hit information for queries with impacts.
	/// SceneQueryFlag flags can be passed to scene query functions, as an optimization, to cause the SDK to only generate specific members of this structure.
	/// </summary>
	public ref class LocationHit : QueryHit
	{
		internal:
			void PopulateUnmanaged(PxLocationHit& hit);
			void PopulateManaged(PxLocationHit hit);

		public:
			property HitFlag Flags;

			/// <summary>
			/// World-space impact point (flag: HitFlag.Position).
			/// </summary>
			property Vector3 Position;

			/// <summary>
			/// World-space impact normal (flag: HitFlag.Normal).
			/// </summary>
			property Vector3 Normal;

			/// <summary>
			/// Distance to hit (flag: HitFlag.Distance).
			/// </summary>
			property float Distance;
	};
};