#pragma once

#include "CookingEnum.h"

namespace PhysX
{
	public ref class Bvh33MidphaseDesc
	{
	internal:
		static PxBVH33MidphaseDesc ToUnmanaged(Bvh33MidphaseDesc^ managed);
		static Bvh33MidphaseDesc^ ToManaged(PxBVH33MidphaseDesc unmanaged);

	public:
		void SetToDefault();
		bool IsValid();

		/// <summary>
		/// Controls the trade - off between mesh size and runtime performance.
		/// </summary>
		property float MeshSizePerformanceTradeOff;

		/// <summary>
		/// Mesh cooking hint.
		/// Used to specify mesh hierarchy construction preference.
		/// </summary>
		property MeshCookingHint MeshCookingHint;
	};
}