#pragma once

#include "CookingEnum.h"

namespace PhysX
{
	public ref class Bvh34MidphaseDesc
	{
	internal:
		static PxBVH34MidphaseDesc ToUnmanaged(Bvh34MidphaseDesc^ managed);
		static Bvh34MidphaseDesc^ ToManaged(PxBVH34MidphaseDesc unmanaged);

	public:
		void SetToDefault();
		bool IsValid();

		/// <summary>
		/// Mesh cooking hint for max triangles per leaf limit. Less triangles per leaf produces larger meshes with better runtime performance and worse cooking performance. More triangles per leaf results in faster cooking speed and smaller mesh sizes, but with worse runtime performance. 
		/// </summary>
		property int PrimitivesPerLeaf;
	};
}