#pragma once


namespace PhysX
{
	/// <summary>
	/// Identifies each type of actor.
	/// </summary>
	public enum class ActorType
	{
		/// <summary>
		/// A static rigid body.
		/// </summary>
		RigidStatic = PxActorType::eRIGID_STATIC,

		/// <summary>
		/// A dynamic rigid body.
		/// </summary>
		RigidDynamic = PxActorType::eRIGID_DYNAMIC,
		
		/// <summary>
		/// A particle system.
		/// </summary>
		ParticleSystem = PxActorType::ePARTICLE_SYSTEM,

		/// <summary>
		/// A particle fluid.
		/// </summary>
		ParticleFluid = PxActorType::ePARTICLE_FLUID,

		/// <summary>
		/// A cloth.
		/// </summary>
		Cloth = PxActorType::eCLOTH,

		/// <summary>
		/// An articulation link.
		/// </summary>
		ArticulationLink = PxActorType::eARTICULATION_LINK
	};

	/// <summary>
	/// Flags which control the behavior of an actor.
	/// </summary>
	public enum class ActorFlag
	{
		/// <summary>
		/// Enable debug renderer for this actor.
		/// </summary>
		Visualization = PxActorFlag::eVISUALIZATION,
		/// <summary>
		/// Disables scene gravity for this actor.
		/// </summary>
		DisableGravity = PxActorFlag::eDISABLE_GRAVITY,
		/// <summary>
		/// Enables the sending of PxSimulationEventCallback::onWake() and PxSimulationEventCallback::onSleep() notify events.
		/// </summary>
		SendSleepNotifies = PxActorFlag::eSEND_SLEEP_NOTIFIES
	};

	/// <summary>
	/// Identifies each type of actor for retrieving actors from a scene.
	/// </summary>
	public enum class ActorTypeSelectionFlag
	{
		/// <summary>
		/// A static rigid body.
		/// </summary>
		RigidStatic = PxActorTypeSelectionFlag::eRIGID_STATIC,

		/// <summary>
		/// A dynamic rigid body.
		/// </summary>
		Dynamic = PxActorTypeSelectionFlag::eRIGID_DYNAMIC,

		/// <summary>
		/// A particle system.
		/// </summary>
		ParticleSystem = PxActorTypeSelectionFlag::ePARTICLE_SYSTEM,
		
		/// <summary>
		/// A particle fluid.
		/// </summary>
		ParticleFluid = PxActorTypeSelectionFlag::ePARTICLE_FLUID,
		
		/// <summary>
		/// A cloth.
		/// </summary>
		Cloth = PxActorTypeSelectionFlag::eCLOTH
	};

	/// <summary>
	/// Parameter to addForce() and addTorque() calls, determines the exact operation that is carried out.
	/// </summary>
	public enum class ForceMode
	{
		/// <summary>
		/// Parameter has unit of mass * distance/ time^2, i.e. a force.
		/// </summary>
		Force = PxForceMode::eFORCE,

		/// <summary>
		/// Parameter has unit of mass * distance /time.
		/// </summary>
		Impulse = PxForceMode::eIMPULSE, 

		/// <summary>
		/// Parameter has unit of distance / time, i.e. the effect is mass independent: a velocity change.
		/// </summary>
		VelocityChange = PxForceMode::eVELOCITY_CHANGE, 

		/// <summary>
		/// Parameter has unit of distance/ time^2, i.e. an acceleration. It gets treated just like a force except the mass is not divided out before integration.
		/// </summary>
		Acceleration = PxForceMode::eACCELERATION
	};

	/// <summary>
	/// Collection of flags describing the behavior of a dynamic rigid body.
	/// </summary>
	public enum class RigidDynamicFlags
	{
		/// <summary>
		/// Enables kinematic mode for the actor.
		/// Kinematic actors are special dynamic actors that are not influenced by forces (such as gravity),
		/// and have no momentum. They are considered to have infinite mass and can be moved around the world
		/// using the moveKinematic() method. They will push regular dynamic actors out of the way.
		/// Kinematics will not collide with static or other kinematic objects.
		/// 
		/// Kinematic actors are great for moving platforms or characters, where direct motion control is desired.
		/// 
		/// You can not connect Reduced joints to kinematic actors. Lagrange joints work ok if the platform is
		/// moving with a relatively low, uniform velocity.
		/// </summary>
		Kinematic = PxRigidDynamicFlag::eKINEMATIC,

		/// <summary>
		/// Use the kinematic target transform for scene queries.
		/// If this flag is raised, then scene queries will treat the kinematic target
		/// transform as the current pose of the body (instead of using the actual pose).
		/// Without this flag, the kinematic target will only take effect with respect
		/// to scene queries after a simulation step.
		/// </summary>
		UseKinematicTargetForSceneQueries = PxRigidDynamicFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES
	};

	public enum class RigidBodyFlag
	{
		Kinematic = PxRigidBodyFlag::eKINEMATIC,
		UseKinematicTargetForSceneQueries = PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES,
		EnableCCD = PxRigidBodyFlag::eENABLE_CCD,
		EnableCCDFriction = PxRigidBodyFlag::eENABLE_CCD_FRICTION
	};
};