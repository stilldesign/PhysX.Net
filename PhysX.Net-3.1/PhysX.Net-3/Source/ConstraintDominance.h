#pragma once

#include <PxScene.h> 

namespace PhysX
{
	public value class ConstraintDominance
	{
		public:
			ConstraintDominance(float dominance0, float dominance1);

		internal:
			static ConstraintDominance ToManaged(PxConstraintDominance constraintDominance);
			static PxConstraintDominance ToUnmanaged(ConstraintDominance constraintDominance);

		public:
			property float Dominance0;
			property float Dominance1;
	};
};