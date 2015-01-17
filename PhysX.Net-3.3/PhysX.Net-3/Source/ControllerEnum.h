#pragma once


namespace PhysX
{
	public enum class ControllerBehaviorFlag
	{
		CctCanRideOnObject = PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT,
		CctSlide = PxControllerBehaviorFlag::eCCT_SLIDE,
		CctUserDefinedRide = PxControllerBehaviorFlag::eCCT_USER_DEFINED_RIDE
	};
};