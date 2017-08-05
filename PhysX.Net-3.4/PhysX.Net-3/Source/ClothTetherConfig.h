#pragma once

namespace PhysX
{
	public ref class ClothTetherConfig
	{
	public:
		ClothTetherConfig();
		ClothTetherConfig(float stiffness, float stretchLimit);

	internal:
		static PxClothTetherConfig ToUnmanaged(ClothTetherConfig^ m);
		static ClothTetherConfig^ ToManaged(PxClothTetherConfig u);

	public:
		/// <summary>
		/// Stiffness of the tether constraints.
		/// </summary>
		property float Stiffness;

		/// <summary>
		/// Scale of tether lengths when applying tether constraints.
		/// </summary>
		property float StretchLimit;
	};
};