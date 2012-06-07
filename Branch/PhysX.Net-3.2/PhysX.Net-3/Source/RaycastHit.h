#pragma once

#include "SceneQueryImpactHit.h"
#include <PxSceneQueryReport.h> 

namespace PhysX
{
	/// <summary>
	/// Raycast hit information.
	/// </summary>
	public ref class RaycastHit : SceneQueryImpactHit
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