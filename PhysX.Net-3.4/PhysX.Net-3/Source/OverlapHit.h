#pragma once

#include "LocationHit.h"

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class OverlapHit : LocationHit
	{
	internal:
		static PxOverlapHit ToUnmanaged(OverlapHit^ hit);
		static OverlapHit^ ToManaged(PxOverlapHit& hit);

	public:
		
	};
}