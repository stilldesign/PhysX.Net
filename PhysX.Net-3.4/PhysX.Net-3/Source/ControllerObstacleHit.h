#pragma once

#include "ControllerHit.h"

namespace PhysX
{
	public ref class ControllerObstacleHit : ControllerHit
	{
		internal:
			static ControllerObstacleHit^ ToManaged(PxControllerObstacleHit hit);

		public:
			
	};
};