#pragma once

#include "CookingEnum.h"
#include "TolerancesScale.h"

namespace PhysX
{
	ref class MidphaseDesc;

	/// <summary>
	/// Structure describing parameters affecting mesh cooking.
	/// </summary>
	public ref class CookingParams
	{
	internal:
		static PxCookingParams ToUnmanaged(CookingParams^ params);
		static CookingParams^ ToManaged(PxCookingParams params);

	public:
		property float SkinWidth;
		property bool SuppressTriangleMeshRemapTable;
		property TolerancesScale Scale;
		property bool BuildTriangleAdjacencies;
		property MeshPreprocessingFlag MeshPreprocessParams;
		property PhysX::MeshCookingHint MeshCookingHint;
		property float MeshWeldTolerance;
		property float MeshSizePerformanceTradeOff;
		property float AreaTestEpsilon;
		property ConvexMeshCookingType ConvexMeshCookingType;
		property bool BuildGPUData;
		property int GaussMapLimit;
		/// <summary>
		/// Controls the desired midphase desc structure for triangle meshes.
		/// </summary>
		property MidphaseDesc^ MidphaseDesc;
		property float PlaneTolerance;
	};
};