#pragma once

#include "ControllerEnum.h"
#include "Shape.h"
#include "Controller.h"

namespace PhysX
{
	class InternalControllerBehaviorCallback;

	ref class Obstacle;

	public ref class ControllerBehaviorCallback abstract : IDisposable
	{
	public:
		/// <summary>Raised before any disposing is performed.</summary>
		virtual event EventHandler^ OnDisposing;
		/// <summary>Raised once all disposing is performed.</summary>
		virtual event EventHandler^ OnDisposed;

	private:
		InternalControllerBehaviorCallback* _internalCallback;

	protected:
		ControllerBehaviorCallback();
		~ControllerBehaviorCallback();
	public:
		!ControllerBehaviorCallback();

		property bool Disposed
		{
			virtual bool get();
		}

		/// <summary>
		/// Retrieve behavior flags for a shape.
		/// When the CCT touches a shape, the CCT's behavior w.r.t. this shape can be customized
		/// by users. This function retrives the desired ControllerBehaviorFlag flags capturing
		/// the desired behavior.
		/// </summary>
		virtual ControllerBehaviorFlags GetBehaviorFlags(Shape^ shape, Actor^ actor) abstract;

		/// <summary>
		/// Retrieve behavior flags for a controller.
		/// When the CCT touches a controller, the CCT's behavior w.r.t. this controller can be customized
		/// by users. This function retrives the desired PxControllerBehaviorFlag flags capturing
		/// the desired behavior.
		/// </summary>
		virtual ControllerBehaviorFlags GetBehaviorFlags(Controller^ controller) abstract;

		/// <summary>
		/// 
		/// </summary>
		virtual ControllerBehaviorFlags GetBehaviorFlags(Obstacle^ obstacle) abstract;
	
	internal:
		property InternalControllerBehaviorCallback* UnmanagedPointer
		{
			InternalControllerBehaviorCallback* get();
		}
	};

	//

	class InternalControllerBehaviorCallback : public PxControllerBehaviorCallback
	{
	private:
		gcroot<ControllerBehaviorCallback^> _managed;

	public:
		InternalControllerBehaviorCallback(gcroot<ControllerBehaviorCallback^> managed);

		virtual PxControllerBehaviorFlags getBehaviorFlags(const PxShape &shape, const PxActor &actor);
		virtual PxControllerBehaviorFlags getBehaviorFlags(const PxController &controller);
		virtual PxControllerBehaviorFlags getBehaviorFlags(const PxObstacle &obstacle);
	};
};