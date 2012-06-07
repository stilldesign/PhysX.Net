#pragma once

#include "ClothCollisionSphere.h"
#include <PxClothCollisionData.h>

namespace PhysX
{
	/// <summary>
	/// Collision data used for cloth-sphere and cloth-capsule collision.
	/// This structure is used to define radius and position of all the collision spheres.
	/// Furthermore, it is possible to build collision capsules between the specified spheres by providing
	/// index pairs pointing into the sphere data array
	/// Note: one can reuse the same sphere to create multiple capsules sharing the sphere.
	/// However, duplicating the same capsules will hurt the performance as well as the stability of the solver.
	/// </summary>
	public ref class ClothCollisionData
	{
	internal:
		static PxClothCollisionData ToUnmanaged(ClothCollisionData^ data);

	public:
		void SetToDefault();
		bool IsValid();

		property array<ClothCollisionSphere>^ Spheres;
		property array<int>^ PairIndices;
	};
};