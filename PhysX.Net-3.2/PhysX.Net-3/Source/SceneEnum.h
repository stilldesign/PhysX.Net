#pragma once

#include <PxVisualizationParameter.h>
#include <PxSceneQueryReport.h>
#include <PxSceneDesc.h>
#include <PxSceneQueryFiltering.h>

namespace PhysX
{
	public enum class SceneFlag
	{
		/// <summary>
		/// Used to disable use of SSE in the solver.
		/// SSE is detected at runtime(on appropriate platforms) and used if present by default.
		/// However use of SSE can be disabled, even if present, using this flag.
		/// </summary>
		DisableSSE = PxSceneFlag::eDISABLE_SSE,
		/// <summary>
		/// Enable Active Transform Notification.
		/// This flag enables the the Active Transform Notification feature for a scene. This feature
		/// defaults to disabled. When disabled, the function PxScene::getActiveTransforms() will
		/// always return a NULL list.
		/// Note: There may be a performance penalty for enabling the Active Transform Notification,
		/// hence this flag should only be enabled if the application intends to use the feature.
		/// Default: False 
		/// </summary>
		EnableActiveTransforms = PxSceneFlag::eENABLE_ACTIVETRANSFORMS,
		/// <summary>
		/// Enables a second broad phase check after integration that makes it possible to prevent objects
		/// from tunneling through eachother. eSWEPT_INTEGRATION_LINEAR requires this flag to be specified.
		/// Note: For this feature to be effective for shapes that can move at a significant velocity, the
		/// user should raise the flag PxShapeFlag::eUSE_SWEPT_BOUNDS for them.
		/// </summary>
		SweptIntegration = PxSceneFlag::eENABLE_SWEPT_INTEGRATION,
		/// <summary>
		/// Enable adaptive forces to accelerate convergence of the solver.
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// Default: true 
		/// </summary>
		AdaptiveForce = PxSceneFlag::eADAPTIVE_FORCE,
		/// <summary>
		/// Enable contact pair filtering between kinematic and static rigid bodies.
		/// By default contacts between kinematic and static rigid bodies are
		/// suppressed (see PxFilterFlag::eSUPPRESS) and don't get reported to the filter
		/// mechanism. Raise this flag if these pairs should go through the filtering pipeline nonetheless.
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// Default: false 
		/// </summary>
		EnableKinematicStaticPairs = PxSceneFlag::eENABLE_KINEMATIC_STATIC_PAIRS,
		/// <summary>
		/// Enable contact pair filtering between kinematic rigid bodies.
		/// By default contacts between kinematic bodies are
		/// suppressed (see PxFilterFlag::eSUPPRESS) and don't get reported to the
		/// filter mechanism. Raise this flag if these pairs should go through the filtering pipeline nonetheless.
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// Default: false 
		/// </summary>
		EnableKinematicPairs = PxSceneFlag::eENABLE_KINEMATIC_PAIRS,
		/// <summary>
		/// Enable one directional per-contact friction model.
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// Default: false 
		/// </summary>
		EnableOneDirectionFriction = PxSceneFlag::eENABLE_ONE_DIRECTIONAL_FRICTION,
		/// <summary>
		/// Enable two directional per-contact friction model.
		/// Note that this flag is not mutable, and must be set in PxSceneDesc at scene creation.
		/// Default: false 
		/// </summary>
		EnableTwoDirectionalFriction = PxSceneFlag::eENABLE_TWO_DIRECTIONAL_FRICTION,
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
		DisableContactReportBufferSize = PxSceneFlag::eDISABLE_CONTACT_REPORT_BUFFER_RESIZE
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
		/// Visualize the bodies joint projection group.
		/// </summary>
		JointGroups = PxVisualizationParameter::eBODY_JOINT_GROUPS,
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
		CollisionPairs = PxVisualizationParameter::eCOLLISION_PAIRS,
		/// <summary>
		/// Joint local axes.
		/// </summary>
		JointLocalFrames = PxVisualizationParameter::eJOINT_LOCAL_FRAMES,
		/// <summary>
		/// Joint limits.
		/// </summary>
		JointLimits = PxVisualizationParameter::eJOINT_LIMITS,
		/// <summary>
		/// Particle position visualization.
		/// </summary>
		ParticleSystemPosition = PxVisualizationParameter::ePARTICLE_SYSTEM_POSITION,
		/// <summary>
		/// Particle velocity visualization.
		/// </summary>
		ParticleSystemVelocity = PxVisualizationParameter::ePARTICLE_SYSTEM_VELOCITY,
		/// <summary>
		/// Particle collision normal visualization.
		/// </summary>
		ParticleSystemCollisionNormal = PxVisualizationParameter::ePARTICLE_SYSTEM_COLLISION_NORMAL,
		/// <summary>
		/// ParticleSystem AABB visualization.
		/// </summary>
		ParticleSystemBounds = PxVisualizationParameter::ePARTICLE_SYSTEM_BOUNDS,
		/// <summary>
		/// Particle grid visualization.
		/// </summary>
		ParticleSystemGrid = PxVisualizationParameter::ePARTICLE_SYSTEM_GRID,
		/// <summary>
		/// Particle system broad phase bounds.
		/// </summary>
		ParticleSystemBroadphaseBounds = PxVisualizationParameter::ePARTICLE_SYSTEM_BROADPHASE_BOUNDS,
		/// <summary>
		/// ParticleSystem maximum motion distance visualization.
		/// </summary>
		ParticleSystemMaxMotionDistance = PxVisualizationParameter::ePARTICLE_SYSTEM_MAX_MOTION_DISTANCE,
		/// <summary>
		/// Debug visualization culling.
		/// </summary>
		CullBox = PxVisualizationParameter::eCULL_BOX
	};

	public enum class SceneQueryFlags
	{
		Impact = PxSceneQueryFlag::eIMPACT,
		Normal = PxSceneQueryFlag::eNORMAL,
		Distance = PxSceneQueryFlag::eDISTANCE,
		UV = PxSceneQueryFlag::eUV,
		InitialOverlap = PxSceneQueryFlag::eINITIAL_OVERLAP,
		InitialOverlapKeep = PxSceneQueryFlag::eINITIAL_OVERLAP_KEEP,
		TouchingHit = PxSceneQueryFlag::eTOUCHING_HIT,
		BlockingHit = PxSceneQueryFlag::eBLOCKING_HIT,
		All = Impact | Normal | Distance | UV | InitialOverlap | InitialOverlapKeep | TouchingHit | BlockingHit
	};

	/// <summary>
	/// Filtering flags for scene queries.
	/// </summary>
	public enum class SceneQueryFilterFlag
	{
		/// <summary>
		/// Traverse static shapes.
		/// </summary>
		Static = PxSceneQueryFilterFlag::eSTATIC,
		/// <summary>
		/// Traverse dynamic shapes.
		/// </summary>
		Dynamic = PxSceneQueryFilterFlag::eDYNAMIC, 
		/// <summary>
		/// Run the pre-intersection-test filter (see <see cref="SceneQueryFilterCallback.PreFilter" />). 
		/// </summary>
		Prefilter = PxSceneQueryFilterFlag::ePREFILTER,
		/// <summary>
		/// Run the post-intersection-test filter (see <see cref="SceneQueryFilterCallback.PostFilter" />).
		/// </summary>
		PostFilter = PxSceneQueryFilterFlag::ePOSTFILTER,
		/// <summary>
		/// Generate all hits for meshes rather than just the first - NOT CURRENTLY SUPPORTED.
		/// </summary>
		MeshMultiple = PxSceneQueryFilterFlag::eMESH_MULTIPLE,
		/// <summary>
		/// Generate hits for exit points and back faces of tris - NOT CURRENTLY SUPPORTED.
		/// </summary>
		Backface = PxSceneQueryFilterFlag::eBACKFACE
	};
};