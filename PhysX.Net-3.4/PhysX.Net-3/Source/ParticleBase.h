#pragma once

#include "Actor.h"
#include "ParticleEnum.h"

namespace PhysX
{
	ref class ParticleReadData;
	ref class ParticleCreationData;
	value class FilterData;

	/// <summary>
	/// The particle base class represents the shared module for particle based simulation.
	/// </summary>
	public ref class ParticleBase abstract : Actor
	{
		internal:
			ParticleBase(PxParticleBase* particleBase, PhysX::Physics^ owner);

		public:
			/// <summary>
			/// Locks the particle data and provides the data descriptor for accessing the particles.
			/// After reading from the buffers the application needs to call ParticleReadData.Unlock() before
			/// any SDK operation can access the buffers. Particularly the buffers need to be unlocked before
			/// calling ParticleBase.LockParticleReadData(), ParticleBase.CreateParticles(), ParticleBase.ReleaseParticles(), Scene.FetchResults().
			/// </summary>
			ParticleReadData^ LockParticleReadData();

			/// <summary>
			/// Creates new particles.
			/// The ParticleCreationData descriptor is used to create new particles. For each particle successfully created
			/// an index in the range of [0, ParticleBaseDesc.MaxParticles-1] is reserved.
			/// These new particle indices are written to the user memory defined by the indexBuffer parameter, unless the
			/// user sets IndexBuffer to null. The new particles can be immediately read from the application readable particle
			/// data, ParticleReadData.
			/// </summary>
			/// <returns>Number of successfully created particles.</returns>
			int CreateParticles(ParticleCreationData^ creationData);

			/// <summary>
			/// Releases all particles.
			/// Application readable particle data is updated accordingly.
			/// </summary>
			void ReleaseParticles();
			/// <summary>
			/// Releases particles.
			/// Particles corresponding to passed indices are released. Releasing a particle will immediately mark the
			/// particle in the application readable particle data, ParticleReadData, as being invalid, removing ParticleFlag.Valid.
			/// Passing duplicate indices is not allowed.
			/// </summary>
			/// <param name="numberOfParticles">Number of particles to be released.</param>
			/// <param name="indexBuffer">Structure describing indices of particles that should be deleted. (Has to be consistent with numParticles).</param>
			void ReleaseParticles(int numberOfParticles, [Optional] array<PxU32>^ indexBuffer);

			/// <summary>
			/// Sets particle positions.
			/// Directly sets the positions of particles. The supplied positions are used to change particles in
			/// the order of the indices listed in the index buffer. Duplicate indices are allowed. A position
			/// buffer of stride zero is allowed. Application readable particle data is updated accordingly.
			/// </summary>
			/// <param name="positions">Structure describing positions for position updates. (Has to be consistent with numParticles).</param>
			/// <param name="indexBuffer">Structure describing indices of particles that should be updated. (Has to be consistent with numParticles).</param>
			void SetPositions(array<Vector3>^ positions, array<int>^ indexBuffer);

			/// <summary>
			/// Sets particle velocities.
			/// Directly sets the velocities of particles. The supplied velocities are used to change particles in the order of the
			/// indices listed in the index buffer. Duplicate indices are allowed. A velocity buffer of stride zero is allowed.
			/// Application readable particle data is updated accordingly.
			/// </summary>
			/// <param name="positions">Structure describing indices of particles that should be updated. (Has to be consistent with numParticles).</param>
			/// <param name="indexBuffer">Structure describing velocities for velocity updates. (Has to be consistent with numParticles).</param>
			void SetVelocities(array<Vector3>^ positions, array<int>^ indexBuffer);

			/// <summary>
			/// Sets particle rest offsets.
			/// Directly sets the rest offsets of particles. The supplied rest offsets are used to change particles
			/// in the order of the indices listed in the index buffer. Duplicate indices are allowed. A rest offset
			/// buffer of stride zero is allowed. Application readable particle data is updated accordingly.
			/// </summary>
			/// <param name="positions">Structure describing indices of particles that should be updated. (Has to be consistent with numParticles).</param>
			/// <param name="indexBuffer">Structure describing indices of particles that should be updated. (Has to be consistent with numParticles).</param>
			void SetRestOffsets(array<Vector3>^ positions, array<int>^ indexBuffer);

			/// <summary>
			/// Set forces to be applied to the particles when the simulation starts.
			/// This call is ignored on particle system that aren't assigned to a scene.
			/// </summary>
			/// <param name="forceBuffer">Structure describing values for particle updates depending on forceMode. (Has to be consistent with numParticles).</param>
			/// <param name="indexBuffer">Structure describing indices of particles that should be updated. (Has to be consistent with numParticles).</param>
			/// <param name="forceMode">Describes type of update.</param>
			void AddForces(array<Vector3>^ positions, array<int>^ indexBuffer, ForceMode forceMode);

			/// <summary>
			/// Gets or sets the particle system damping (must be nonnegative).
			/// </summary>
			property float Damping
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the external acceleration applied to each particle at each time step.
			/// </summary>
			property Vector3 ExternalAcceleration
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the plane the particles are projected to.
			/// </summary>
			property Plane ProjectionPlane
			{
				Plane get();
				void set(Plane value);
			}

			/// <summary>
			/// Gets or sets the mass of a particle.
			/// </summary>
			property float ParticleMass
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the restitution used for collision with shapes.
			/// </summary>
			property float Restitution
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the dynamic friction used for collision with shapes.
			/// </summary>
			property float DynamicFriction
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the static friction used for collision with shapes.
			/// </summary>
			property float StaticFriction
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the user definable collision filter data.
			/// </summary>
			property FilterData SimulationFilterData
			{
				FilterData get();
				void set(FilterData value);
			}

			/// <summary>
			/// Marks the object to reset interactions and re-run collision filters in the next simulation step.
			/// </summary>
			void ResetFiltering();

			/// <summary>
			/// Gets the maximum number of particles for this particle system.
			/// </summary>
			property int MaximumParticles
			{
				int get();
			}

			/// <summary>
			/// Gets the maximal motion distance (the particle can move the maximal distance of getMaxMotionDistance() during one timestep).
			/// </summary>
			property float MaximumMotionDistance
			{
				float get();
			}

			/// <summary>
			/// Gets the distance between particles and collision geometry, which is maintained during simulation.
			/// </summary>
			property float RestOffset
			{
				float get();
			}

			/// <summary>
			/// Gets the distance at which contacts are generated between particles and collision geometry.
			/// </summary>
			property float ContactOffset
			{
				float get();
			}

			/// <summary>
			/// Gets the particle grid size used for internal spatial data structures.
			/// </summary>
			property float GridSize
			{
				float get();
			}

			/// <summary>
			/// Gets the particle read data flags.
			/// </summary>
			property PhysX::ParticleReadDataFlag ParticleReadDataFlags
			{
				PhysX::ParticleReadDataFlag get();
			}

			/// <summary>
			/// Gets or sets the particle system flags.
			/// </summary>
			property ParticleBaseFlag Flags
			{
				ParticleBaseFlag get();
				void set(ParticleBaseFlag value);
			}

		internal:
			property PxParticleBase* UnmanagedPointer
			{
				PxParticleBase* get() new;
			}
	};
};