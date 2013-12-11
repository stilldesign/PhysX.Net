#pragma once

#include "ParticleReadData.h"

namespace PhysX
{
	public ref class ParticleFluidReadData : ParticleReadData
	{
		internal:
			ParticleFluidReadData(PxParticleFluidReadData* particleBase);

		public:
			array<float>^ GetDensityBuffer();

		internal:
			property PxParticleFluidReadData* UnmanagedPointer
			{
				PxParticleFluidReadData* get() new;
			}
	};
};