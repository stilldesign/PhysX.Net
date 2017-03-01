#pragma once

#include "Geometry.h"

namespace PhysX
{
	/// <summary>
	/// A class representing the geometry of a sphere.
	/// Spheres are defined by their radius.
	/// The scaling of the sphere is expected to be baked into this value, there is no additional scaling parameter.
	/// </summary>
	public ref class SphereGeometry : Geometry
	{
		public:
			SphereGeometry();
			SphereGeometry(float radius);
		internal:
			SphereGeometry(PxSphereGeometry geom);

		internal:
			virtual PxGeometry* ToUnmanaged() override;
			static SphereGeometry^ ToManaged(PxSphereGeometry sphere);

		public:
			property float Radius;
	};
};