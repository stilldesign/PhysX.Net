#pragma once

#include "ClothFabricPhase.h"

namespace PhysX
{
	public ref class ClothFabricDesc
	{
	internal:
		static PxClothFabricDesc ToUnmanaged(ClothFabricDesc^ managed);

	public:
		property int NumberOfParticles;
		property array<ClothFabricPhase>^ Phases;
		property array<int>^ Sets;
		property array<int>^ Indices;
		property array<float>^ RestValues;
		property array<int>^ TetherAnchors;
		property array<float>^ TetherLengths;
	};
}