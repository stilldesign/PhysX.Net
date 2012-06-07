#pragma once

#include "ClothEnum.h"

namespace PhysX
{
	/// <summary>
	/// Solver configuration parameters for a cloth fabric phase type.
	/// </summary>
	public ref class ClothPhaseSolverConfig
	{
	internal:
		static ClothPhaseSolverConfig^ ToManaged(PxClothPhaseSolverConfig config);
		static PxClothPhaseSolverConfig ToUnmanaged(ClothPhaseSolverConfig^ config);

	public:
		/// <summary>
		/// The type of solver to use for a specific phase type.
		/// </summary>
		property ClothPhaseSolverType SolverType;

		/// <summary>
		/// Stiffness of the cloth solver.
		/// </summary>
		property float Stiffness;

		/// <summary>
		/// Stiffness of the cloth solver under certain limits.
		/// </summary>
		property float StretchStiffness;

		/// <summary>
		/// Limit to control when stretchStiffness has to be applied.
		/// </summary>
		property float StretchLimit;
	};
};