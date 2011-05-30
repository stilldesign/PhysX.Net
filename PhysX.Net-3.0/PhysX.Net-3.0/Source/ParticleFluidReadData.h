#pragma once

#include "ParticleReadData.h"

class PxParticleFluidReadData;

namespace PhysX
{
	/// <summary>
	/// Data layout descriptor for reading fluid particle data from the SDK.
	/// </summary>
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