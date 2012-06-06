#pragma once

#include "ControllerEnum.h"
#include "Shape.h"
#include "Controller.h"

namespace PhysX
{
	public ref class ControllerBehaviorCallback
	{
	private:
		PxControllerBehaviorCallback* _callback;

	protected:
		ControllerBehaviorCallback();
		~ControllerBehaviorCallback();
	public:
		!ControllerBehaviorCallback();

		/// <summary>
		/// Retrieve behavior flags for a shape.
		/// When the CCT touches a shape, the CCT's behavior w.r.t. this shape can be customized
		/// by users. This function retrives the desired ControllerBehaviorFlag flags capturing
		/// the desired behavior.
		/// </summary>
		ControllerBehaviorFlag GetBehaviorFlags(Shape^ shape);

		/// <summary>
		/// Retrieve behavior flags for a controller.
		/// When the CCT touches a controller, the CCT's behavior w.r.t. this controller can be customized
		/// by users. This function retrives the desired PxControllerBehaviorFlag flags capturing
		/// the desired behavior.
		/// </summary>
		ControllerBehaviorFlag GetBehaviorFlags(Controller^ controller);

		/// <summary>
		/// 
		/// </summary>
		//ControllerBehaviorFlag GetBehaviorFlags(Obstacle^ obstacle);
	
	internal:
		property PxControllerBehaviorCallback* UnmanagedPointer
		{
			PxControllerBehaviorCallback* get();
		}
	};
};