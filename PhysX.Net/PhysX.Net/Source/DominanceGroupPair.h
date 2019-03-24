#pragma once


namespace PhysX
{
	public value class DominanceGroupPair
	{
		public:
			DominanceGroupPair(float dominance0, float dominance1);

		internal:
			static DominanceGroupPair ToManaged(PxDominanceGroupPair constraintDominance);
			static PxDominanceGroupPair ToUnmanaged(DominanceGroupPair constraintDominance);

		public:
			property float Dominance0;
			property float Dominance1;
	};
};