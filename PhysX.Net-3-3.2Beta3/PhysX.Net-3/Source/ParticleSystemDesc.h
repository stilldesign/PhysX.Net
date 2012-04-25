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

			virtual void SetToDefault([Optional] Nullable<TolerancesScale> scale) override;
			virtual bool IsValid() override;

		internal:
			static PxParticleSystemDesc ToUnmanaged(ParticleSystemDesc^ desc);
	};
};