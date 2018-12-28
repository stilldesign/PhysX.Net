#pragma once

namespace PhysX
{
	[Flags]
	public enum class MaterialFlags
	{
		DisableFriction = PxMaterialFlag::eDISABLE_FRICTION,
		DisableStrongFriction = PxMaterialFlag::eDISABLE_STRONG_FRICTION
	};
};