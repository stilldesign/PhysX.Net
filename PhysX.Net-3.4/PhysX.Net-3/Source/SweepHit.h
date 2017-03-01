#pragma once

#include "LocationHit.h"

namespace PhysX
{
	/// <summary>
	/// This structure captures results for a single sweep query.
	/// </summary>
	public ref class SweepHit : LocationHit
	{
	internal:
		static PxSweepHit ToUnmanaged(SweepHit^ hit);
		static SweepHit^ ToManaged(PxSweepHit hit);

	public:
		property bool HadInitialOverlap;
	};
};