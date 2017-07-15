#pragma once


namespace PhysX
{
	[Flags]
	public enum class ConstraintFlag
	{
		Broken = PxConstraintFlag::eBROKEN,
		ProjectToActor0 = PxConstraintFlag::ePROJECT_TO_ACTOR0,
		ProjectToActor1 = PxConstraintFlag::ePROJECT_TO_ACTOR1,
		Projection = PxConstraintFlag::ePROJECTION,
		CollisionEnabled = PxConstraintFlag::eCOLLISION_ENABLED,
		Visualization = PxConstraintFlag::eVISUALIZATION,
		DriveLimitsAreForces = PxConstraintFlag::eDRIVE_LIMITS_ARE_FORCES,
		ImprovedSlerp = PxConstraintFlag::eIMPROVED_SLERP,
		DisableProcessing = PxConstraintFlag::eDISABLE_PREPROCESSING,
		GpuCompatible = PxConstraintFlag::eGPU_COMPATIBLE
	};

	/// <summary>
	/// Unique identifiers for extensions classes which implement a constraint based on Constraint.
	/// </summary>
	public enum class ConstraintExtIds
	{
		Joint = PxConstraintExtIDs::eJOINT, 
		VehicleSuspensionLimit = PxConstraintExtIDs::eVEHICLE_SUSP_LIMIT, 
		VehicleStickyTyre = PxConstraintExtIDs::eVEHICLE_STICKY_TYRE, 
		NextFreeId = PxConstraintExtIDs::eNEXT_FREE_ID, 
		InvalidId = PxConstraintExtIDs::eINVALID_ID
	};

	public enum class PvdUpdateType
	{
		CreateInstance = PxPvdUpdateType::CREATE_INSTANCE,
		ReleaseInstance = PxPvdUpdateType::RELEASE_INSTANCE,
		UpdateAllProperties = PxPvdUpdateType::UPDATE_ALL_PROPERTIES,
		UpdateSimProperties = PxPvdUpdateType::UPDATE_SIM_PROPERTIES
	};

	public enum class Constraint1DFlag
	{
		Spring = Px1DConstraintFlag::eSPRING,
		AccelerationSpring = Px1DConstraintFlag::eACCELERATION_SPRING,
		Restitution = Px1DConstraintFlag::eRESTITUTION,
		KeepBias = Px1DConstraintFlag::eKEEPBIAS,
		OutputForce = Px1DConstraintFlag::eOUTPUT_FORCE
	};

	/// <summary>
	/// Constraint type hints which the solver uses to optimize constraint handling.
	/// </summary>
	public enum class ConstraintSolveHint
	{
		None = PxConstraintSolveHint::eNONE,
		Acceleration = PxConstraintSolveHint::eACCELERATION1,
		SlerpSpring = PxConstraintSolveHint::eSLERP_SPRING,
		Acceleration2 = PxConstraintSolveHint::eACCELERATION2,
		Acceleration3 = PxConstraintSolveHint::eACCELERATION3,
		Equality = PxConstraintSolveHint::eEQUALITY,
		Inequality = PxConstraintSolveHint::eINEQUALITY
	};
};