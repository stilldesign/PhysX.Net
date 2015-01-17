#pragma once

#include "LockedData.h"
#include "ClothParticle.h"

namespace PhysX
{
	public ref class ClothParticleData : LockedData
	{
	internal:
		ClothParticleData(physx::PxClothParticleData* data, int particleCount);

	public:
		property array<ClothParticle>^ Particles;
		property array<ClothParticle>^ PreviousParticles;
	};
};