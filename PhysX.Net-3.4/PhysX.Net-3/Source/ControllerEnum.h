#pragma once


namespace PhysX
{
	[Flags]
	public enum class ControllerBehaviorFlags
	{
		CctCanRideOnObject = PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT,
		CctSlide = PxControllerBehaviorFlag::eCCT_SLIDE,
		CctUserDefinedRide = PxControllerBehaviorFlag::eCCT_USER_DEFINED_RIDE
	};
};