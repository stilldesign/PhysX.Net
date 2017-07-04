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
	[Flags]
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
	[Flags]
	public enum class ActorTypeFlag
	{
		/// <summary>
		/// A static rigid body.
		/// </summary>
		RigidStatic = PxActorTypeFlag::eRIGID_STATIC,

		/// <summary>
		/// A dynamic rigid body.
		/// </summary>
		RigidDynamic = PxActorTypeFlag::eRIGID_DYNAMIC,

		/// <summary>
		/// A particle system.
		/// </summary>
		ParticleSystem = PxActorTypeFlag::ePARTICLE_SYSTEM,
		
		/// <summary>
		/// A particle fluid.
		/// </summary>
		ParticleFluid = PxActorTypeFlag::ePARTICLE_FLUID,
		
		/// <summary>
		/// A cloth.
		/// </summary>
		Cloth = PxActorTypeFlag::eCLOTH
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

	public enum class RigidBodyFlag
	{
		Kinematic = PxRigidBodyFlag::eKINEMATIC,
		UseKinematicTargetForSceneQueries = PxRigidBodyFlag::eUSE_KINEMATIC_TARGET_FOR_SCENE_QUERIES,
		EnableCCD = PxRigidBodyFlag::eENABLE_CCD,
		EnableCCDFriction = PxRigidBodyFlag::eENABLE_CCD_FRICTION,
		EnablePoseIntegrationPreview = PxRigidBodyFlag::eENABLE_POSE_INTEGRATION_PREVIEW,
		EnableSpeculativeCCD = PxRigidBodyFlag::eENABLE_SPECULATIVE_CCD
	};
};