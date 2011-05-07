#pragma once

namespace PhysX
{
	public enum class SceneFlag
	{
		DisableSSE = PxSceneFlag::eDISABLE_SSE,
		EnableActiveTransforms = PxSceneFlag::eENABLE_ACTIVETRANSFORMS,
		SweptIntegration = PxSceneFlag::eENABLE_SWEPT_INTEGRATION,
		AdaptiveForce = PxSceneFlag::eADAPTIVE_FORCE,
		EnableKinematicStaticPairs = PxSceneFlag::eENABLE_KINEMATIC_STATIC_PAIRS,
		EnableKinematicPairs = PxSceneFlag::eENABLE_KINEMATIC_PAIRS
	};
};