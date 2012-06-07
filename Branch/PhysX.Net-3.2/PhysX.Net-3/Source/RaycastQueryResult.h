#pragma once

#include <PxBatchQueryDesc.h> 

namespace PhysX
{
	ref class RaycastHit;

	public ref class RaycastQueryResult
	{
	internal:
		static RaycastQueryResult^ ToManaged(PxRaycastQueryResult result);
		static PxRaycastQueryResult ToUnmanaged(RaycastQueryResult^ result);

	public:
		property array<RaycastHit^>^ Hits;
		property int QueryStatus;
	};
};