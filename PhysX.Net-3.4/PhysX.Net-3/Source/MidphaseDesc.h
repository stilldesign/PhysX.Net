#pragma once

#include "TriangleMeshEnum.h"

namespace PhysX
{
	ref class Bvh33MidphaseDesc;
	ref class Bvh34MidphaseDesc;

	public ref class MidphaseDesc
	{
	internal:
		static PxMidphaseDesc ToUnmanaged(MidphaseDesc^ managed);
		static MidphaseDesc^ ToManaged(PxMidphaseDesc unmanaged);

	public:
		bool IsValid();

		property Nullable<MeshMidPhase> Type
		{
			Nullable<MeshMidPhase> get();
		}

		property Bvh33MidphaseDesc^ Bvh33Desc;
		property Bvh34MidphaseDesc^ Bvh34Desc;
	};
}