#pragma once


namespace PhysX
{
	[Flags]
	public enum class ClothFlag
	{
		/// <summary>
		/// Default value
		/// </summary>
		Default = PxClothFlag::eDEFAULT,

		/// <summary>
		/// Use CUDA to simulate cloth.
		/// </summary>
		CUDA = PxClothFlag::eCUDA,

		/// <summary>
		/// Turn on/off gpu based solver.
		/// </summary>
		[Obsolete]
		GPU = PxClothFlag::eGPU,

		/// <summary>
		/// Use swept contact (continuous collision).
		/// </summary>
		SweptContact = PxClothFlag::eSWEPT_CONTACT,

		/// <summary>
		/// Collide against rigid body shapes in scene.
		/// </summary>
		SceneCollision = PxClothFlag::eSCENE_COLLISION
	};
};