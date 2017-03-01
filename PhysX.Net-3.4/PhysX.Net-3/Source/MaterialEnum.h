#pragma once

namespace PhysX
{
	public enum class MaterialFlag : PxU32
	{
		DisableFriction = PxMaterialFlag::eDISABLE_FRICTION,
		DisableStrongFriction = PxMaterialFlag::eDISABLE_STRONG_FRICTION
	};
};