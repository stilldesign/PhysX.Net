#pragma once


 namespace PhysX
 {
	[Flags]
	public enum class ConvexFlag
	{
		/// <summary>
		/// Denotes the use of 16-bit vertex indices in PxConvexMeshDesc::triangles. (otherwise, 32-bit indices are assumed).
		/// </summary>
		Indices16Bit = PxConvexFlag::e16_BIT_INDICES,

		/// <summary>
		/// Automatically recomputes the hull from the vertices. If this flag is not set, you must provide the entire geometry manually.
		/// </summary>
		ComputeConvex = PxConvexFlag::eCOMPUTE_CONVEX,

		/// <summary>
		/// Checks and removes almost zero - area triangles during convex hull computation.The rejected area size is specified in PxCookingParams::areaTestEpsilon.
		/// Note:
		/// This flag is only used in combination with eCOMPUTE_CONVEX.
		///	If this flag is used in combination with eINFLATE_CONVEX, the newly added triangles by the inflation algorithm are not checked(size of the triangles depends on PxCooking::skinWidth).
		/// </summary>
		CheckZeroAreaTriangles = PxConvexFlag::eCHECK_ZERO_AREA_TRIANGLES,

		QuantizeInput = PxConvexFlag::eQUANTIZE_INPUT,
		DisableMeshValidation = PxConvexFlag::eDISABLE_MESH_VALIDATION,
		PlaneShifting = PxConvexFlag::ePLANE_SHIFTING,
		FastInertiaComputation = PxConvexFlag::eFAST_INERTIA_COMPUTATION,
		GpuCompatible = PxConvexFlag::eGPU_COMPATIBLE,
		ShiftVertices = PxConvexFlag::eSHIFT_VERTICES
	};

	[Flags]
	public enum class MeshPreprocessingFlag
	{
		/// <summary>
		/// When set, mesh welding is performed. See PxCookingParams::meshWeldTolerance. Clean mesh must be enabled.
		/// </summary>
		WeldVertices = PxMeshPreprocessingFlag::eWELD_VERTICES,

		/// <summary>
		/// When set, mesh cleaning is disabled. This makes cooking faster.
		/// When clean mesh is not performed, mesh welding is also not performed.
		/// It is recommended to use only meshes that passed during validateTriangleMesh.
		/// </summary>
		DisableCleanMesh = PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH,

		/// <summary>
		/// When set, active edges are set for each triangle edge. This makes cooking faster but slow up contact generation.
		/// </summary>
		DisableActiveEdgesPrecompute = PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE,

		Force32BitIndices = PxMeshPreprocessingFlag::eFORCE_32BIT_INDICES
	};

	public enum class MeshCookingHint
	{
		/// <summary>
		/// Default value. Favors higher quality hierarchy with higher runtime performance over cooking speed.
		/// </summary>
		SimulationPerformance = PxMeshCookingHint::eSIM_PERFORMANCE,

		/// <summary>
		/// Enables fast cooking path at the expense of somewhat lower quality hierarchy construction.
		/// </summary>
		CookingPerformance = PxMeshCookingHint::eCOOKING_PERFORMANCE
	};

	public enum class ConvexMeshCookingResult
	{
		Success = PxConvexMeshCookingResult::eSUCCESS,
		ZeroAreaTestFailed = PxConvexMeshCookingResult::eZERO_AREA_TEST_FAILED,
		Failure = PxConvexMeshCookingResult::eFAILURE
	};

	public enum class TriangleMeshCookingResult
	{
		Success = PxTriangleMeshCookingResult::eSUCCESS,
		LargeTriangle = PxTriangleMeshCookingResult::eLARGE_TRIANGLE,
		Failure = PxTriangleMeshCookingResult::eFAILURE
	};

	public enum class ConvexMeshCookingType
	{
		QuickHull = PxConvexMeshCookingType::eQUICKHULL
	};
 };