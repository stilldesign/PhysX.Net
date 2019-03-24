#pragma once

#include "LocationHit.h"

namespace PhysX
{
	/// <summary>
	/// Raycast hit information.
	/// </summary>
	public ref class RaycastHit : LocationHit
	{
	internal:
		static PxRaycastHit ToUnmanaged(RaycastHit^ hit);
		static RaycastHit^ ToManaged(PxRaycastHit& hit);

	public:
		/// <summary>
		/// Barycentric coordinates of hit point, for triangle mesh and height field (flag: SceneQueryFlag.UV).
		/// </summary>
		property float U;

		/// <summary>
		/// Barycentric coordinates of hit point, for triangle mesh and height field (flag: SceneQueryFlag.UV).
		/// </summary>
		property float V;
	};
};