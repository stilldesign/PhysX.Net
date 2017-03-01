#pragma once


namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public enum class ParticleBaseFlag
	{
		/// <summary>
		/// Enable/disable two way collision of particles with the rigid body scene. In either case, particles are
		/// influenced by colliding rigid bodies. If CollisionTwoway is not set, rigid bodies are not influenced
		/// by colliding particles. Use PxParticleBaseDesc.ParticleMass to control the strength of the feedback
		/// force on rigid bodies.
		/// </summary>
		CollisionTwoway = PxParticleBaseFlag::eCOLLISION_TWOWAY,

		/// <summary>
		/// Enable/disable execution of particle simulation.
		/// </summary>
		Enabled = PxParticleBaseFlag::eENABLED,

		/// <summary>
		/// Defines whether the particles of this particle system should be projected to a plane.
		/// This can be used to build 2D applications, for instance. The projection plane is defined by the parameter
		/// ParticleBaseDesc.ProjectionPlaneNormal and ParticleBaseDesc.ProjectionPlaneDistance.
		/// </summary>
		ProjectToPlane = PxParticleBaseFlag::ePROJECT_TO_PLANE,

		/// <summary>
		/// Enable/disable per particle rest offsets. Per particle rest offsets can be used to support particles having
		/// different sizes with respect to collision.
		/// </summary>
		PerParticleRestOffset = PxParticleBaseFlag::ePER_PARTICLE_REST_OFFSET,

		/// <summary>
		/// Ename/disable per particle collision caches. Per particle collision caches improve collision detection
		/// performance at the cost of increased memory usage.
		/// Note:
		/// Switching this flag while the particle system is part of a scene might have a negative impact on performance. 
		/// </summary>
		PerParticleCollisionCacheHint = PxParticleBaseFlag::ePER_PARTICLE_COLLISION_CACHE_HINT,

		/// <summary>
		/// Enable/disable GPU acceleration. This configuration cannot be changed while the particle system is part of a scene.
		/// </summary>
		GPU = PxParticleBaseFlag::eGPU
	};

	/// <summary>
	/// Flags to configure PxParticleBase simulation output that can be read by the application.
	/// Disabling unneeded buffers saves memory and improves performance.
	/// </summary>
	public enum class ParticleReadDataFlag
	{
		/// <summary>
		/// Enables reading particle positions from the SDK.
		/// </summary>
		PositionBuffer = PxParticleReadDataFlag::ePOSITION_BUFFER,

		/// <summary>
		/// Enables reading particle velocities from the SDK.
		/// </summary>
		VelocityBuffer = PxParticleReadDataFlag::eVELOCITY_BUFFER,

		/// <summary>
		/// Enables reading per particle rest offsets from the SDK. Per particle rest offsets are never changed by the simulation.
		/// </summary>
		RestOffsetBuffer = PxParticleReadDataFlag::eREST_OFFSET_BUFFER,

		/// <summary>
		/// Enables reading particle flags from the SDK.
		/// </summary>
		FlagsBuffer = PxParticleReadDataFlag::eFLAGS_BUFFER,

		/// <summary>
		/// Enables reading particle collision normals from the SDK.
		/// </summary>
		CollisionNormalBuffer = PxParticleReadDataFlag::eCOLLISION_NORMAL_BUFFER,

		/// <summary>
		/// Enables reading particle collision velocities from the SDK.
		/// </summary>
		CollisionVelocityBuffer = PxParticleReadDataFlag::eCOLLISION_VELOCITY_BUFFER,

		/// <summary>
		/// Enables reading particle densities from the SDK. (ParticleFluid only).
		/// </summary>
		DensityBuffer = PxParticleReadDataFlag::eDENSITY_BUFFER
	};

	/// <summary>
	/// Particle flags are used for additional information on the particles.
	/// </summary>
	public enum class ParticleFlag
	{
		/// <summary>
		/// Marks a valid particle. The particle data corresponding to these particle flags is valid,
		/// i.e. defines a particle, when set. Particles that are not marked with PxParticleFlag::eVALID
		/// are ignored during simulation.
		/// </summary>
		Valid = PxParticleFlag::eVALID,

		/// <summary>
		/// Marks a particle that has collided with a static actor shape.
		/// </summary>
		CollisionWithStatic = PxParticleFlag::eCOLLISION_WITH_STATIC,

		/// <summary>
		/// Marks a particle that has collided with a dynamic actor shape.
		/// </summary>
		CollisionWithDynamic = PxParticleFlag::eCOLLISION_WITH_DYNAMIC,

		/// <summary>
		/// Marks a particle that has collided with a shape that has been flagged as a drain (See ShapeFlag.ParticleDrain).
		/// </summary>
		CollisionWithDrain = PxParticleFlag::eCOLLISION_WITH_DRAIN,

		/// <summary>
		/// Marks a particle that had to be ignored for simulation, because the spatial data structure ran out of resources.
		/// </summary>
		SpatialDataStructureOverflow = PxParticleFlag::eSPATIAL_DATA_STRUCTURE_OVERFLOW,
	};
};