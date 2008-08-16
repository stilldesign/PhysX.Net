#pragma once

#include <NxController.h> 

namespace StillDesign
{
	namespace PhysX
{
		public enum class ControllerType
		{
			Box = NX_CONTROLLER_BOX,
			Capsule = NX_CONTROLLER_CAPSULE
		};
		
		public enum class ControllerAction
		{
			None = NX_ACTION_NONE,
			Push = NX_ACTION_PUSH
		};
		
		public enum class ControllerCollisionFlag
		{
			Sides = NXCC_COLLISION_SIDES,
			Up = NXCC_COLLISION_UP,
			Down = NXCC_COLLISION_DOWN
		};
		
		public enum class CCTInteractionFlag
		{
			Include = NXIF_INTERACTION_INCLUDE,
			Exclude = NXIF_INTERACTION_EXCLUDE,
			UseFilter = NXIF_INTERACTION_USE_FILTER
		};
	};
};