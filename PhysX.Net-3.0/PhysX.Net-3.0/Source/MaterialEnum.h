#pragma once

namespace PhysX
{
	public enum class MaterialFlag : PxU32
	{
		Ansiotropic = PxMaterialFlag::eANISOTROPIC,
		DisableFriction = PxMaterialFlag::eDISABLE_FRICTION,
		DisableStrongFriction = PxMaterialFlag::eDISABLE_STRONG_FRICTION
	};

	public enum class CombineMode
	{
		Average = PxCombineMode::eAVERAGE,
		Minimum = PxCombineMode::eMIN,
		Multiply = PxCombineMode::eMULTIPLY,
		Max = PxCombineMode::eMAX
	};
};