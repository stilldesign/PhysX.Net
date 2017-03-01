#pragma once

#include "Geometry.h"

namespace PhysX
{
	/// <summary>
	/// Class representing the geometry of a capsule.
	/// Capsules are shaped as the union of a cylinder of length 2 * halfHeight and with the given radius centered at the
	/// origin and extending along the x axis, and two hemispherical ends.
	/// The scaling of the capsule is expected to be baked into these values, there is no additional scaling parameter
	/// </summary>
	public ref class CapsuleGeometry : Geometry
	{
		public:
			CapsuleGeometry();
			CapsuleGeometry(float radius, float halfHeight);

		internal:
			virtual PxGeometry* ToUnmanaged() override;
			static CapsuleGeometry^ ToManaged(PxCapsuleGeometry capsule);

		public:
			property float Radius;
			property float HalfHeight;
	};
};