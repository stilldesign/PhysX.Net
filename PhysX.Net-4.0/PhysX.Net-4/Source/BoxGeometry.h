#pragma once

#include "Geometry.h"

namespace PhysX
{
	/// <summary>
	/// Class representing the geometry of a box.
	/// The geometry of a box can be fully specified by its half extents. This is the half of its width, height, and depth.
	/// The scaling of the box is expected to be baked into these values, there is no additional scaling parameter.
	/// </summary>
	public ref class BoxGeometry : Geometry
	{
		public:
			BoxGeometry();
			BoxGeometry(float hX, float hY, float hZ);
			BoxGeometry(Vector3 halfExtents);

		internal:
			virtual PxGeometry* ToUnmanaged() override;
			static BoxGeometry^ ToManaged(PxBoxGeometry box);

		public:
			property Vector3 HalfExtents;

			/// <summary>
			/// Gets or sets the size of the box.
			/// This property is simply a helper which returns HalfExtents * 2 and the inverse when setting.
			/// </summary>
			property Vector3 Size
			{
				Vector3 get();
				void set(Vector3 value);
			}
	};
};