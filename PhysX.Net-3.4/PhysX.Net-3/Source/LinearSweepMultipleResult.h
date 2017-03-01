#pragma once

namespace PhysX
{
	ref class SweepHit;

	public ref class LinearSweepMultipleResult
	{
	public:
		property array<SweepHit^>^ Hits;
		property array<int>^ HitShapeIndices;

		property SweepHit^ Block;
		property int BlockingShapeIndex;
		property bool Overflow;
	};
};