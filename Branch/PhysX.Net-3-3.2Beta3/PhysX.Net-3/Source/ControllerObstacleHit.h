#pragma once

#include "CctHit.h"

namespace PhysX
{
	public ref class ControllerObstacleHit : CctHit
	{
		internal:
			static ControllerObstacleHit^ ToManaged(PxControllerObstacleHit hit);

		public:
			
	};
};