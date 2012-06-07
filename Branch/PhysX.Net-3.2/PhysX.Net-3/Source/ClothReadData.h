#pragma once

#include "LockedData.h"
#include "ClothParticle.h"
#include <PxClothTypes.h> 
#include <PxClothReadData.h>

namespace PhysX
{
	public ref class ClothReadData : LockedData
	{
	internal:
		ClothReadData(PxClothReadData* data, int particleCount);

	public:
		property array<ClothParticle>^ Particles;
		property array<ClothParticle>^ PreviousParticles;
	};
};