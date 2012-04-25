#pragma once

#include "ActorDesc.h"
#include "FilterData.h"
#include "ParticleEnum.h"
#include "TolerancesScale.h"

namespace PhysX
{
	/// <summary>
	/// ParticleBase Descriptor.
	/// This structure is used to save and load the state of ParticleSystem and ParticleFluid objects.
	/// </summary>
	public ref class ParticleBaseDesc abstract : ActorDesc
	{
		protected:
			ParticleBaseDesc(ActorType type, [Optional] Nullable<TolerancesScale> scale);
	
		internal:
			void PopulateManaged(PxParticleBaseDesc& desc);
			void PopulateUnmanaged(PxParticleBaseDesc& desc);

		public:
			virtual void SetToDefault([Optional] Nullable<TolerancesScale> scale);
			virtual bool IsValid() abstract;

			/// <summary>
			/// Gets or sets the maximal number of particles for the particle system used in the simulation.
			/// </summary>
			property int MaximumParticles;

			/// <summary>
			/// Maximal distance a particle is allowed to travel within one time step.
			/// </summary>
			property float MaximumMotionDistance;

			/// <summary>
			/// Specifies a skin around the particles within which contacts will be generated
			/// </summary>
			property float ContactOffset;

			/// <summary>
			/// Specifies an offset at which particles will come to rest relative to an objects surface
			/// </summary>
			property float RestOffset;

			/// <summary>
			/// This parameter controls the parallelization of the particle system
			/// </summary>
			property float GridSize;

			/// <summary>
			/// Velocity damping constant, which is globally applied to each particle
			/// </summary>
			property float Damping;

			/// <summary>
			/// Acceleration (m/s^2) applied to all particles at all time steps
			/// </summary>
			property Vector3 ExternalAcceleration;

			/// <summary>
			/// Defines the normal of the plane the particles are projected to.
			/// This parameter is only used if PxParticleBaseFlag::ePROJECT_TO_PLANE is set.
			/// </summary>
			property Vector3 ProjectionPlaneNormal;

			/// <summary>
			/// Defines the constant term of the plane the particles are projected to.
			/// This parameter is only used if PxParticleBaseFlag::ePROJECT_TO_PLANE is set
			/// </summary>
			property float ProjectionPlaneDistance;

			/// <summary>
			/// Defines the mass of a particle
			/// </summary>
			property float ParticleMass;

			/// <summary>
			/// Defines the restitution coefficient used for collisions of the particles with shapes
			/// </summary>
			property float Restitution;

			/// <summary>
			/// Defines the dynamic friction of the particles regarding the surface of a shape
			/// </summary>
			property float DynamicFriction;

			/// <summary>
			/// Defines the static friction of the particles regarding the surface of a shape
			/// </summary>
			property float StaticFriction;

			/// <summary>
			/// User definable data for collision filtering
			/// </summary>
			property FilterData SimulationFilterData;

			/// <summary>
			/// Flags defining certain properties of the particle system
			/// </summary>
			property ParticleBaseFlag ParticleBaseFlags;

			/// <summary>
			/// Flags to control which data can be read from the SDK.
			/// Default: PxParticleReadDataFlag::ePOSITION_BUFFER | PxParticleReadDataFlag::eID_BUFFER | PxParticleReadDataFlag::eFLAGS_BUFFER
			/// </summary>
			property ParticleReadDataFlag ParticleReadDataFlags;
	};
};