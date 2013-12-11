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

			array<int>^ GetValidParticleBitmap();
			array<Vector3>^ GetPositions();
			array<Vector3>^ GetVelocities();
			array<float>^ GetRestOffsets();
			array<ParticleFlag>^ GetFlags();
			array<Vector3>^ GetCollisionNormals();

			property PhysX::DataAccessFlag DataAccessFlag
			{
				virtual PhysX::DataAccessFlag get() override;
			}

			property int NumberOfValidParticles
			{
				int get();
			}

			property int ValidParticleRange
			{
				int get();
			}

		internal:
			property PxParticleReadData* UnmanagedPointer
			{
				virtual PxParticleReadData* get() new;
			}
	};
};