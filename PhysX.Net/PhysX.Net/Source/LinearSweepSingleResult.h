#pragma once

namespace PhysX
{
	ref class SweepHit;

	public ref class LinearSweepSingleResult
	{
	public:
		property SweepHit^ ClosestHit;
		property int ShapeIndex;
	};
};