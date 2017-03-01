#pragma once

using namespace System::Runtime::InteropServices;

namespace PhysX
{
	/// <summary>
	/// Sphere representation used for cloth-capsule collision.
	/// Cloth can collide with capsules. Each capsule is represented by a pair of spheres with possibly different radi.
	/// </summary>
	[StructLayout(LayoutKind::Sequential)]
	public value class ClothCollisionSphere
	{
	public:
		/// <summary>
		/// Gets or sets the position of the sphere.
		/// </summary>
		property Vector3 Position;

		/// <summary>
		/// Gets or sets the radius of the sphere.
		/// </summary>
		property float Radius;
	};
};