#pragma once

#include "CharacterEnum.h"
#include "Controller.h"

namespace PhysX
{
	ref class ControllerManager;

	/// <summary>
	/// A capsule character controller.
	/// </summary>
	/// <remarks>
	/// The capsule is defined as a position, a vertical height, and a radius. The height is the distance between
	/// the two sphere centers at the end of the capsule. In other words:
	///
	/// p = pos (returned by controller)
	/// h = height
	/// r = radius
	/// 
	/// p = center of capsule
	/// top sphere center = p.y + h*0.5
	/// bottom sphere center = p.y - h*0.5
	/// top capsule point = p.y + h*0.5 + r
	/// bottom capsule point = p.y - h*0.5 - r
	/// </remarks>
	public ref class CapsuleController : Controller
	{
		internal:
			CapsuleController(PxCapsuleController* capsuleController, PhysX::ControllerManager^ controllerManager);

		public:
			/// <summary>Gets or sets the controller's radius.</summary>
			property float Radius
			{
				float get();
				void set(float value);
			}

			/// <summary>Gets or sets the extents of Capsule.</summary>
			property float Height
			{
				float get();
				void set(float value);
			}

			/// <summary>Gets or sets the controller's climbing mode.</summary>
			property CapsuleClimbingMode ClimbingMode
			{
				CapsuleClimbingMode get();
				void set(CapsuleClimbingMode value);
			}

		internal:
			property PxCapsuleController* UnmanagedPointer
			{
				PxCapsuleController* get() new;
			}
	};
};