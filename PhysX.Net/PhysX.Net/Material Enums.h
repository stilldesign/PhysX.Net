#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public enum class MaterialFlag
		{
			Ansiotropic = NX_MF_ANISOTROPIC,
			DisableFriction = NX_MF_DISABLE_FRICTION,
			DisableStrongFriction = NX_MF_DISABLE_STRONG_FRICTION
		};
		public enum class CombineMode
		{
			Average = NX_CM_AVERAGE,
			Minimum = NX_CM_MIN,
			Multiply = NX_CM_MULTIPLY,
			Max = NX_CM_MAX
		};
	};
};