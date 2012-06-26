#pragma once

#include <PxController.h>
#include <PxControllerBehavior.h>

namespace PhysX
{
	public enum class ControllerBehaviorFlag
	{
		CctCanRideOnObject = PxControllerBehaviorFlag::eCCT_CAN_RIDE_ON_OBJECT,
		CctSlide = PxControllerBehaviorFlag::eCCT_SLIDE
	};
};