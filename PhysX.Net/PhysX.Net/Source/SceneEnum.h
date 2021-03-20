#pragma once


namespace PhysX
{
	[Flags]
	public enum class SceneFlag
	{
		EnableActiveActors = PxSceneFlag::eENABLE_ACTIVE_ACTORS,

		/// <summary>
		/// Enables a second broad phase check after integration that makes it possible to prevent objects
		/// from tunneling through eachother. eSWEPT_INTEGRATION_LINEAR requires this flag to be specified.
		/// Note: For this feature to be effective for shapes that can move at a significant velocity, the
		/// user should raise the flag PxShapeFlag::eUSE_SWEPT_BOUNDS for them.
		/// </summary>
		EnableCcd = PxSceneFlag::eENABLE_CCD,

		DisableCcdResweep = PxSceneFlag::eDISABLE_CCD_RESWEEP,

		/// <summary>
		/// Enable adaptive forces to accelerate convergence of the solver.
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// Default: true 
		/// </summary>
		AdaptiveForce = PxSceneFlag::eADAPTIVE_FORCE,

		/// <summary>
		/// Enable GJK-based distance collision detection system.
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// In order to use this system, we need to register the system in the PxCreatePhysics
		/// Default: false 
		/// </summary>
		EnablePcm = PxSceneFlag::eENABLE_PCM,

		/// <summary>
		/// Disable contact report buffer resize. Once the contact buffer is full, the rest of
		/// the contact reports will not be buffered and sent. 
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// Default: false 
		/// </summary>
		DisableContactReportBufferSize = PxSceneFlag::eDISABLE_CONTACT_REPORT_BUFFER_RESIZE,

		DisableContactCache = PxSceneFlag::eDISABLE_CONTACT_CACHE,

		RequireReadWriteLock = PxSceneFlag::eREQUIRE_RW_LOCK,

		EnableStabilization = PxSceneFlag::eENABLE_STABILIZATION,
		EnableAveragePoint = PxSceneFlag::eENABLE_AVERAGE_POINT,
		ExcludeKinematicsFromActiveActors = PxSceneFlag::eEXCLUDE_KINEMATICS_FROM_ACTIVE_ACTORS,
		EnableGpuDynamics = PxSceneFlag::eENABLE_GPU_DYNAMICS,
		EnableEnhancedDeterminism = PxSceneFlag::eENABLE_ENHANCED_DETERMINISM,

		MutableFlags = PxSceneFlag::eMUTABLE_FLAGS
	};

	public enum class VisualizationParameter
	{
		/// <summary>
		/// This overall visualization scale gets multiplied with the individual scales.
		/// Setting to zero turns ignores all visualizations. Default is 0.
		/// </summary>
		Scale = PxVisualizationParameter::eSCALE,
		/// <summary>
		/// Visualize the world axes.
		/// </summary>
		WorldAxes = PxVisualizationParameter::eWORLD_AXES,
		/// <summary>
		/// Visualize a bodies axes.
		/// </summary>
		BodyAxes = PxVisualizationParameter::eBODY_AXES,
		/// <summary>
		/// Visualize a body's mass axes. 
		/// This visualization is also useful for visualizing the sleep state of bodies. Sleeping bodies are drawn in black, while
		/// awake bodies are drawn in white. If the body is sleeping and part of a sleeping group, it is drawn in red.
		/// </summary>
		BodyMassAxes = PxVisualizationParameter::eBODY_MASS_AXES,
		/// <summary>
		/// Visualize the bodies linear velocity.
		/// </summary>
		LinearVelocity = PxVisualizationParameter::eBODY_LIN_VELOCITY,
		/// <summary>
		/// Visualize the bodies angular velocity.
		/// </summary>
		AngularVelocity = PxVisualizationParameter::eBODY_ANG_VELOCITY,
		/// <summary>
		/// Visualize contact points. Will enable contact information.
		/// </summary>
		ContactPoint = PxVisualizationParameter::eCONTACT_POINT,
		/// <summary>
		/// Visualize contact normals. Will enable contact information.
		/// </summary>
		ContactNormal = PxVisualizationParameter::eCONTACT_NORMAL,
		/// <summary>
		/// Visualize contact errors. Will enable contact information.
		/// </summary>
		ContactError = PxVisualizationParameter::eCONTACT_ERROR,
		/// <summary>
		/// Visualize Contact forces. Will enable contact information.
		/// </summary>
		ContactForce = PxVisualizationParameter::eCONTACT_FORCE,
		/// <summary>
		/// Visualize actor axes.
		/// </summary>
		ActorAxes = PxVisualizationParameter::eACTOR_AXES,
		/// <summary>
		/// Visualize bounds (AABBs in world space).
		/// </summary>
		CollisionAABB = PxVisualizationParameter::eCOLLISION_AABBS,
		/// <summary>
		/// Shape visualization.
		/// </summary>
		CollisionShapes = PxVisualizationParameter::eCOLLISION_SHAPES,
		/// <summary>
		/// Shape axis visualization.
		/// </summary>
		CollisionAxes = PxVisualizationParameter::eCOLLISION_AXES,
		/// <summary>
		/// Compound visualization (compound AABBs in world space).
		/// </summary>
		CollisionCompounds = PxVisualizationParameter::eCOLLISION_COMPOUNDS,
		/// <summary>
		/// Mesh & convex face normals.
		/// </summary>
		CollisionFaceNormals = PxVisualizationParameter::eCOLLISION_FNORMALS,
		/// <summary>
		/// Active edges for meshes.
		/// </summary>
		CollisionEdges = PxVisualizationParameter::eCOLLISION_EDGES,
		/// <summary>
		/// Static pruning structures.
		/// </summary>
		CollisionStatic = PxVisualizationParameter::eCOLLISION_STATIC,
		/// <summary>
		/// Dynamic pruning structures.
		/// </summary>
		CollisionDynamic = PxVisualizationParameter::eCOLLISION_DYNAMIC,
		///// <summary>
		///// Convex decomposition of triangle meshes.
		///// </summary>
		//CollisionConvexParts = PxVisualizationParameter::eCOLLISION_CONVEX_PARTS,
		/// <summary>
		/// Visualizes pairwise state.
		/// </summary>
		DeprecatedCollisionPairs = PxVisualizationParameter::eDEPRECATED_COLLISION_PAIRS,
		/// <summary>
		/// Joint local axes.
		/// </summary>
		JointLocalFrames = PxVisualizationParameter::eJOINT_LOCAL_FRAMES,
		/// <summary>
		/// Joint limits.
		/// </summary>
		JointLimits = PxVisualizationParameter::eJOINT_LIMITS,
		/// <summary>
		/// Debug visualization culling.
		/// </summary>
		CullBox = PxVisualizationParameter::eCULL_BOX,
		/// <summary>
		/// MBP regions.
		/// </summary>
		MBPRegions = PxVisualizationParameter::eMBP_REGIONS
	};

	public enum class HitFlag
	{
		/// <summary>
		/// "position" member of PxQueryHit is valid.
		/// </summary>
		Position = PxHitFlag::ePOSITION,

		/// <summary>
		/// "normal" member of PxQueryHit is valid.
		/// </summary>
		Normal = PxHitFlag::eNORMAL,

		/// <summary>
		/// "u" and "v" barycentric coordinates of PxQueryHit are valid. Not applicable to sweep queries.
		/// </summary>
		UV = PxHitFlag::eUV,

		/// <summary>
		/// Performance hint flag for sweeps when it is known upfront there's no initial overlap. NOTE: using this flag may cause undefined results if shapes are initially overlapping.
		/// </summary>
		AssumeInitialOverlapDisabled = PxHitFlag::eASSUME_NO_INITIAL_OVERLAP,

		/// <summary>
		/// Report all hits for meshes rather than just the first. On SPU the number of reported hits per mesh is limited to 16 in no specific order.
		/// </summary>
		MeshMultiple = PxHitFlag::eMESH_MULTIPLE,

		/// <summary>
		/// Report any first hit for meshes. If neither eMESH_MULTIPLE or eMESH_ANY is specified, a single closest hit will be reported for meshes.
		/// </summary>
		MeshAny = PxHitFlag::eMESH_ANY,

		/// <summary>
		/// Report hits with back faces of triangles. Also report hits for raycast originating on mesh surface and facing away from the surface normal.
		/// </summary>
		MeshBothSides = PxHitFlag::eMESH_BOTH_SIDES,

		/// <summary>
		/// Use more accurate but slower narrow phase sweep tests. May provide better compatibility with PhysX 3.2 sweep behavior. Ignored on SPU.
		/// </summary>
		PreciseSweep = PxHitFlag::ePRECISE_SWEEP,

		/// <summary>
		/// Report the minimum translation depth, normal and contact point. Ignored on SPU.
		/// </summary>
		MinimumTranslationDirection = PxHitFlag::eMTD,

		/// <summary>
		/// 
		/// </summary>
		Default = PxHitFlag::eDEFAULT,

		/// <summary>
		/// Only this subset of flags can be modified by pre-filter. Other modifications will be discarded.
		/// </summary>
		ModifiableFlags = PxHitFlag::eMODIFIABLE_FLAGS
	};

	/// <summary>
	/// Filtering flags for scene queries.
	/// </summary>
	public enum class QueryFlag
	{
		/// <summary>
		/// Traverse static shapes.
		/// </summary>
		Static = PxQueryFlag::eSTATIC,
		/// <summary>
		/// Traverse dynamic shapes.
		/// </summary>
		Dynamic = PxQueryFlag::eDYNAMIC,
		/// <summary>
		/// Run the pre-intersection-test filter (see <see cref="SceneQueryFilterCallback.PreFilter" />). 
		/// </summary>
		Prefilter = PxQueryFlag::ePREFILTER,
		/// <summary>
		/// Run the post-intersection-test filter (see <see cref="SceneQueryFilterCallback.PostFilter" />).
		/// </summary>
		PostFilter = PxQueryFlag::ePOSTFILTER,
		AnyHit = PxQueryFlag::eANY_HIT,
		NoBlock = PxQueryFlag::eNO_BLOCK
	};

	public enum class QueryHitType
	{
		None = PxQueryHitType::eNONE,
		Block = PxQueryHitType::eBLOCK,
		Touch = PxQueryHitType::eTOUCH
	};

	public enum class SceneQueryUpdateMode
	{
		/// <summary>
		/// Both scene query build and commit are executed.
		/// </summary>
		EnabledCommitEnabled = PxSceneQueryUpdateMode::eBUILD_ENABLED_COMMIT_ENABLED,
		/// <summary>
		/// Scene query build only is executed.
		/// </summary>
		EnabledCommitDisabled = PxSceneQueryUpdateMode::eBUILD_ENABLED_COMMIT_DISABLED,
		/// <summary>
		/// No work is done, no update of scene queries.
		/// </summary>
		DisabledCommitDisabled = PxSceneQueryUpdateMode::eBUILD_DISABLED_COMMIT_DISABLED,
	};

	/// <summary>
	/// Enum for selecting the type of solver used for the simulation.
	/// </summary>
	public enum class SolverType
	{
		/// <summary>
		/// Selects the default iterative sequential impulse solver. This is the same kind of solver
		/// used in PhysX 3.4 and earlier releases.
		/// </summary>
		PGS = PxSolverType::ePGS,

		/// <summary>
		/// Selects a non linear iterative solver. This kind of solver can lead to improved convergence
		/// and handle large mass ratios, long chains and jointed systems better. It is slightly more expensive 
		/// than the default solver and can introduce more energy to correct joint and contact errors.
		/// </summary>
		TGS = PxSolverType::eTGS
	};
};