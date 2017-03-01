#pragma once

using namespace System::Runtime::InteropServices;

namespace PhysX
{
	/// <summary>
	/// Defines position of the cloth particle as well as inverse mass. When inverse mass is set
	/// to 0, the particle gets fully constrained to the position during simulation.
	/// </summary>
	[StructLayout(LayoutKind::Sequential)]
	public value class ClothParticle
	{
	public:
		ClothParticle(Vector3 position, float inverseWeight);

		/// <summary>
		/// Position of the particle (in cloth local space).
		/// </summary>
		property Vector3 Position;

		/// <summary>
		/// Inverse mass of the particle. If set to 0, the particle is fully constrained.
		/// </summary>
		property float InverseWeight;
	};
};