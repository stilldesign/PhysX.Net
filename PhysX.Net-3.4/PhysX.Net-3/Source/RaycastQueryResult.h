#pragma once

#include "PhysicsEnum.h"


namespace PhysX
{
	ref class RaycastHit;

	public ref class RaycastQueryResult
	{
	internal:
		static RaycastQueryResult^ ToManaged(PxRaycastQueryResult result);
		static PxRaycastQueryResult ToUnmanaged(RaycastQueryResult^ result);

	public:
		property bool Block;
		property array<RaycastHit^>^ Touches;
		// TODO: property Object^ UserData;
		property BatchQueryStatus QueryStatus;
		property bool HasBlock;
	};
};