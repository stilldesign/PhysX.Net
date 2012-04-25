#pragma once

#include <PxParticleCreationData.h>

namespace PhysX
{
	/// <summary>
	/// Descriptor-like user-side class describing buffers for particle creation.
	/// </summary>
	public ref class ParticleCreationData
	{
		internal:
			static PxParticleCreationData ToUnmanaged(ParticleCreationData^ data);

		public:
			property int NumberOfParticles;

			property array<Vector3>^ PositionBuffer;
			property array<Vector3>^ VelocityBuffer;
			property array<Vector3>^ RestOffsetBuffer;
			property array<Vector3>^ FlagBuffer;
	};
};