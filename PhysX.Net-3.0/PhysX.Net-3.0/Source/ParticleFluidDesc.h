#pragma once

#include "ParticleBaseDesc.h"

namespace PhysX
{
	/// <summary>
	/// Particle Fluid Descriptor.
	/// This structure is used to save and load the state of ParticleFluid objects.
	/// </summary>
	public ref class ParticleFluidDesc : ParticleBaseDesc
	{
		public:
			ParticleFluidDesc([Optional] Nullable<TolerancesScale> scale);

		internal:
			void PopulateManaged(PxParticleFluidDesc& desc);
			void PopulateUnmanaged(PxParticleFluidDesc& desc);

			static PxParticleFluidDesc ToUnmanaged(ParticleFluidDesc^ desc);
			static ParticleFluidDesc^ ToManaged(PxParticleFluidDesc desc);

		public:
			/// <summary>
			/// Gets or sets the typical particle distance of particles in the rest state (relaxed).
			/// Defines the particle resolution of the fluid.
			/// </summary>
			property float RestParticleDistance;

			/// <summary>
			/// Gets or sets the stiffness of the particle interaction related to the pressure.
			/// </summary>
			property float Stiffness;

			/// <summary>Gets or sets the viscosity of the fluid defines its viscous behavior.</summary>
			property float Viscosity;
	};
};