#pragma once

#include "ParticleBaseDesc.h"

namespace PhysX
{
	/// <summary>
	/// Particle System Descriptor.
	/// This structure is used to save and load the state of ParticleSystem objects.
	/// </summary>
	public ref class ParticleSystemDesc : ParticleBaseDesc
	{
		public:
			ParticleSystemDesc([Optional] Nullable<TolerancesScale> scale);

			void SetToDefault(TolerancesScale scale);
			bool IsValid();

		internal:
			static PxParticleSystemDesc ToUnmanaged(ParticleSystemDesc^ desc);
	};
};