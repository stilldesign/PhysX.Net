#pragma once

#include "ParticleBase.h"

namespace PhysX
{
	ref class ParticleFluidReadData;

	/// <summary>
	/// The particle fluid class represents the main module for particle based fluid simulation.
	/// SPH (Smoothed Particle Hydrodynamics) is used to animate the particles. This class inherits the properties
	/// of the PxParticleBase class and adds particle-particle interactions
	/// </summary>
	public ref class ParticleFluid : ParticleBase
	{
		internal:
			ParticleFluid(PxParticleFluid* particleFluid, PhysX::Physics^ owner);

		public:
			/// <summary>
			/// Locks the particle data and provides the data descriptor for accessing the particles including fluid particle densities.
			/// </summary>
			ParticleFluidReadData^ LockParticleFluidReadData();

			//

			/// <summary>
			/// Gets or sets the fluid stiffness (must be positive).
			/// </summary>
			property float Stiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the fluid viscosity (must be positive).
			/// </summary>
			property float Viscosity
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets the typical distance of particles in the relaxed state of the fluid.
			/// </summary>
			property float RestParticleDistance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets the name of dynamic type.
			/// </summary>
			property String^ ConcreteTypeName
			{
				String^ get();
			}

		internal:
			property PxParticleFluid* UnmanagedPointer
			{
				PxParticleFluid* get() new;
			}
	};
};