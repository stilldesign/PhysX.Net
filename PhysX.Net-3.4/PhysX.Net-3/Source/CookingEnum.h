#pragma once


 namespace PhysX
 {
	public enum class Platform
	{
		PC = PxPlatform::ePC,
		Xenon = PxPlatform::eXENON,
		PlayStation3 = PxPlatform::ePLAYSTATION3,
		ARM = PxPlatform::eARM,
		WiiU = PxPlatform::eWIIU
	};

	public enum class ConvexFlag
	{
		/// <summary>
		/// Used to flip the normals if the winding order is reversed.
		/// The Nx libraries assume that the face normal of a triangle with vertices [a,b,c] can be computed as: edge1 = b-a edge2 = c-a face_normal = edge1 x edge2.
		/// Note: this is the same as counterclockwise winding in a right handed graphics coordinate system.
		/// If this does not match the winding order for your triangles, raise the below flag.
		/// </summary>
		FlipNormals = PxConvexFlag::eFLIPNORMALS,

		/// <summary>
		/// Denotes the use of 16-bit vertex indices in PxConvexMeshDesc::triangles. (otherwise, 32-bit indices are assumed).
		/// </summary>
		Indices16Bit = PxConvexFlag::e16_BIT_INDICES,

		/// <summary>
		/// Automatically recomputes the hull from the vertices. If this flag is not set, you must provide the entire geometry manually.
		/// </summary>
		ComputeConvex = PxConvexFlag::eCOMPUTE_CONVEX,

		/// <summary>
		/// Inflates the convex object according to skin width.
		/// Note: This flag is only used in combination with ComputeConvex.
		/// </summary>
		InflateConvex = PxConvexFlag::eINFLATE_CONVEX,

		/// <summary>
		/// Checks and removes almost zero - area triangles during convex hull computation.The rejected area size is specified in PxCookingParams::areaTestEpsilon.
		/// Note:
		/// This flag is only used in combination with eCOMPUTE_CONVEX.
		///	If this flag is used in combination with eINFLATE_CONVEX, the newly added triangles by the inflation algorithm are not checked(size of the triangles depends on PxCooking::skinWidth).
		/// </summary>
		CheckZeroAreaTriangles = PxConvexFlag::eCHECK_ZERO_AREA_TRIANGLES
	};

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
		DisableActiveEdgesPrecompute = PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE
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
 };