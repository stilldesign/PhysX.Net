#pragma once

#include <PxConstraintDesc.h> 
#include <PxConstraintExt.h>

namespace PhysX
{
	public enum class ConstraintFlag
	{
		Broken = PxConstraintFlag::eBROKEN,
		Projection = PxConstraintFlag::ePROJECTION,
		CollisionEnabled = PxConstraintFlag::eCOLLISION_ENABLED,
		Reporting = PxConstraintFlag::eREPORTING,
		Visualization = PxConstraintFlag::eVISUALIZATION
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

	public enum PvdUpdateType
	{
		CreateInstance = PxPvdUpdateType::CREATE_INSTANCE,
		ReleaseInstance = PxPvdUpdateType::RELEASE_INSTANCE,
		UpdateAllProperties = PxPvdUpdateType::UPDATE_ALL_PROPERTIES,
		UpdateSimProperties = PxPvdUpdateType::UPDATE_SIM_PROPERTIES
	};
};