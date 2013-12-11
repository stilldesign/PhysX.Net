#pragma once

//#include <PxCloth.h> 
#include "ClothEnum.h"

namespace PhysX
{
	/// <summary>
	/// Solver configuration parameters for a cloth fabric phase type.
	/// </summary>
	public ref class ClothPhaseSolverConfig
	{
	internal:
		static ClothPhaseSolverConfig^ ToManaged(PxClothStretchConfig config);
		static PxClothStretchConfig ToUnmanaged(ClothPhaseSolverConfig^ config);

	public:
		/// <summary>
		/// Stiffness of the cloth solver.
		/// </summary>
		property float Stiffness;

		/// <summary>
		/// Stiffness multiplier of the cloth solver under certain limits.
		/// </summary>
		property float StiffnessMultiplier;

		/// <summary>
		/// Limit to control when stiffnessMultiplier has to be applied.
		/// </summary>
		property float CompressionLimit;

		/// <summary>
		/// Limit to control when stretchStiffness has to be applied.
		/// </summary>
		property float StretchLimit;
	};
};