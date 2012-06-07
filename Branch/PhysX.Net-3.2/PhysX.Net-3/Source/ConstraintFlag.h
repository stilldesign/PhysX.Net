#pragma once

#include <PxConstraintDesc.h>

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

	public enum class Constraint1DFlag
	{
		Spring = Px1DConstraintFlag::eSPRING,
		AccelerationSpring = Px1DConstraintFlag::eACCELERATION_SPRING,
		Restitution = Px1DConstraintFlag::eRESTITUTION,
		KeepBias = Px1DConstraintFlag::eKEEPBIAS,
		OutputForce = Px1DConstraintFlag::eOUTPUT_FORCE
	};
};