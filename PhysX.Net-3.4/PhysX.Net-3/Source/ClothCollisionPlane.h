#pragma once

using namespace System::Runtime::InteropServices;

namespace PhysX
{
	/// <summary>
	/// Plane representation used for cloth-convex collision.
	/// Cloth can collide with convexes. Each convex is represented by a mask of the planes that make up the convex.
	/// </summary>
	[StructLayout(LayoutKind::Sequential)]
	public value class ClothCollisionPlane
	{
	public:
		/// <summary>
		/// The normal to the plane.
		/// </summary>
		property Vector3 Normal;

		/// <summary>
		/// The distance from the origin.
		/// </summary>
		property float Distance;
	};
};