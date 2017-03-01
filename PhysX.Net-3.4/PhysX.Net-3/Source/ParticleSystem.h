#pragma once

#include "ParticleBase.h"

namespace PhysX
{
	/// <summary>
	/// The particle system class represents the main module for particle based simulation.
	/// This class inherits the properties of the PxParticleBase class.
	/// The particle system class manages a set of particles. Particles can be created,
	/// released and updated directly through the API. When a particle is created the user
	/// gets an id for it which can be used to address the particle until it is released again.
	///
	/// Particles collide with static and dynamic shapes. They are also affected by the scene gravity
	/// and a user force, as well as global velocity damping. When a particle collides, a particle
	/// flag is raised corresponding to the type of actor, static or dynamic, it collided with.
	/// Additionally a shape can be flagged as a drain (See PxShapeFlag), in order to get a corresponding
	/// particle flag raised when a collision occurs. This information can be used to delete particles.
	///
	/// The particles of a particle system don't collide with each other. In order to simulate particle-particle
	/// interactions use the subclass PxParticleFluid.
	/// </summary>
	public ref class ParticleSystem : ParticleBase
	{
		internal:
			ParticleSystem(PxParticleSystem* particleSystem, PhysX::Physics^ owner);

		public:

		internal:
			property PxParticleSystem* UnmanagedPointer
			{
				PxParticleSystem* get();
			}
	};
};