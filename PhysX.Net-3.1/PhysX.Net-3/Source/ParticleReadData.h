#pragma once

#include "LockedData.h"
#include "ParticleEnum.h"

namespace PhysX
{
	public ref class ParticleReadData : LockedData
	{
		public:
			ParticleReadData(PxParticleReadData* data);

			virtual void Unlock() override;

			/// <summary>
			/// Bitmap marking valid particle indices.
			/// The bitmap is defined between [0, (ParticleReadData.ValidParticleRange-1) >> 5].
			/// </summary>
			array<int>^ GetValidParticleBitmap();
			void SetValidParticleBitmap(array<int>^ bitmap);

			array<Vector3>^ GetPositionBuffer();
			void SetPositionBuffer(array<Vector3>^ value);

			array<Vector3>^ GetVelocityBuffer();
			void SetVelocityBuffer(array<Vector3>^ value);

			array<float>^ GetRestOffsetBuffer();
			void SetRestOffsetBuffer(array<float>^ value);

			array<ParticleFlag>^ GetFlagsBuffer();
			void SetFlagsBuffer(array<ParticleFlag>^ value);

			/// <summary>
			/// Collision normals of colliding particles. The collision normal buffer is only guaranteed
			/// to be valid after the particle system has been simulated. Otherwise collisionNormalBuffer.ptr()
			/// is NULL. This also applies to particle systems that are not assigned to a scene.
			/// </summary>
			array<Vector3>^ GetCollisionNormalBuffer();
			void SetCollisionNormalBuffer(array<Vector3>^ value);

			/// <summary>
			/// Returns DataAccessFlag.Readable.
			/// </summary>
			property PhysX::DataAccessFlag DataAccessFlag
			{
				virtual PhysX::DataAccessFlag get() override;
			}

			/// <summary>
			/// Gets the number of particles (only including particles with ParticleFlag.Valid set).
			/// </summary>
			property int NumberOfValidParticles
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets the index after the last valid particle (ParticleFlag.Valid set). Its 0 if there are no valid particles.
			/// </summary>
			property int ValidParticleRange
			{
				int get();
				void set(int value);
			}

		internal:
			property PxParticleReadData* UnmanagedPointer
			{
				virtual PxParticleReadData* get() new;
			}
	};
};