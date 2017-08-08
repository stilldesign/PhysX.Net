#pragma once

#include "Bounds3.h"

namespace PhysX
{
	public ref class BroadPhaseExt abstract sealed
	{
	public:
		static array<Bounds3>^ CreateRegionsFromWorldBounds(Bounds3 globalBounds, int nbSubdiv, [Optional] Nullable<int> upAxis);
	};
};