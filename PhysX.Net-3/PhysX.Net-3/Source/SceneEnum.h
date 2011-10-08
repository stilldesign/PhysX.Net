#pragma once

#include <PxVisualizationParameter.h>
#include <PxSceneQueryReport.h>
#include <PxSceneDesc.h>
#include <PxSceneQueryFiltering.h>

namespace PhysX
{
	public enum class SceneFlag
	{
		DisableSSE = PxSceneFlag::eDISABLE_SSE,
		EnableActiveTransforms = PxSceneFlag::eENABLE_ACTIVETRANSFORMS,
		SweptIntegration = PxSceneFlag::eENABLE_SWEPT_INTEGRATION,
		AdaptiveForce = PxSceneFlag::eADAPTIVE_FORCE,
		EnableKinematicStaticPairs = PxSceneFlag::eENABLE_KINEMATIC_STATIC_PAIRS,
		EnableKinematicPairs = PxSceneFlag::eENABLE_KINEMATIC_PAIRS
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
		///// <summary>
		///// ParticleSystem drain shape visualization.
		///// </summary>
		//ParticleSystemDrains = PxVisualizationParameter::ePARTICLE_SYSTEM_DRAINS,
		/// <summary>
		/// Deformable mesh visualization.
		/// </summary>
		DeformableMesh = PxVisualizationParameter::eDEFORMABLE_MESH,
		/// <summary>
		/// Deformable attachments visualization.
		/// </summary>
		DeformableAttachments = PxVisualizationParameter::eDEFORMABLE_ATTACHMENTS,
		/// <summary>
		/// Deformable collisions visualization.
		/// </summary>
		DeformableCollisions = PxVisualizationParameter::eDEFORMABLE_COLLISIONS,
		/// <summary>
		/// Deformable self-collisions visualization.
		/// </summary>
		DeformableSelfCollisions = PxVisualizationParameter::eDEFORMABLE_SELFCOLLISIONS,
		/// <summary>
		/// Deformable sleeping visualization.
		/// </summary>
		DeformableSleep = PxVisualizationParameter::eDEFORMABLE_SLEEP,
		/// <summary>
		/// Deformable tearing visualization.
		/// </summary>
		DeformableTearing = PxVisualizationParameter::eDEFORMABLE_TEARING,
		/// <summary>
		/// Deformable valid bounds visualization.
		/// </summary>
		DeformableValidBounds = PxVisualizationParameter::eDEFORMABLE_VALIDBOUNDS,
		/// <summary>
		/// Deformable shapes visualization.
		/// </summary>
		DeformableShapes = PxVisualizationParameter::eDEFORMABLE_SHAPES,
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
		TouchingHit = PxSceneQueryFlag::eTOUCHING_HIT,
		BlockingHit = PxSceneQueryFlag::eBLOCKING_HIT
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