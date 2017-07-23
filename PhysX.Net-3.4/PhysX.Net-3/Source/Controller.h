#pragma once

#include "CharacterEnum.h"

namespace PhysX
{
	ref class ControllerManager;
	ref class ControllerFilters;
	ref class ObstacleContext;
	ref class RigidDynamic;
	ref class Shape;
	ref class ControllerState;
	value class ControllerStats;

	/// <summary>
	/// Base class for character controllers.
	/// </summary>
	public ref class Controller abstract : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxController* _controller;
			PhysX::ControllerManager^ _controllerManager;
			PhysX::RigidDynamic^ _actor;
			PhysX::Shape^ _shape;

		protected:
			Controller(PxController* controller, PhysX::ControllerManager^ owner);
		public:
			~Controller();
		protected:
			!Controller();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			ControllerCollisionFlag Move(Vector3 displacement, TimeSpan elapsedTime);
			ControllerCollisionFlag Move(Vector3 displacement, TimeSpan elapsedTime, float minimumDistance, ControllerFilters^ filters, [Optional] ObstacleContext^ obstacles);

			/// <summary>
			/// Returns information about the controller's internal state. 
			/// </summary>
			ControllerState^ GetState();

			/// <summary>
			/// The character controller uses caching in order to speed up collision testing, this caching
			/// can not detect when static objects have changed in the scene. You need to call this method
			/// when such changes have been made. 
			/// </summary>
			void InvalidateCache();

			/// <summary>
			/// Returns the controller's internal statistics.
			/// </summary>
			ControllerStats GetStats();

			/// <summary>
			/// Resizes the controller.
			/// This function attempts to resize the controller to a given size, while making sure the bottom
			/// position of the controller remains constant. In other words the function modifies both the
			/// height and the (center) position of the controller. This is a helper function that can be used
			/// to implement a 'crouch' functionality for example.
			/// </summary>
			void Resize(float height);

			//

			/// <summary>
			/// Gets the associated controller manager instance.
			/// </summary>
			property PhysX::ControllerManager^ ControllerManager
			{
				PhysX::ControllerManager^ get();
			}

			/// <summary>
			/// Gets the associated actor instance.
			/// </summary>
			property PhysX::RigidDynamic^ Actor
			{
				PhysX::RigidDynamic^ get();
			}

			/// <summary>
			/// Gets the associated shape instance.
			/// </summary>
			property PhysX::Shape^ Shape
			{
				PhysX::Shape^ get();
			}

			/// <summary>
			/// Gets or sets the rigid body actor associated with this controller (see PhysX documentation). The behavior upon manually
			/// altering this actor is undefined, you should primarily use it for reading const properties.
			/// </summary>
			property Vector3 Position
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the "foot" position of the controller, i.e. the position of the bottom of the CCT's shape.
			/// 
			/// Note: The foot position takes the contact offset into account
			/// Warning: When setting, this is a 'teleport' function, it doesn't check for collisions.
			/// </summary>
			property Vector3 FootPosition
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the step height.
			/// </summary>
			property float StepOffset
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the non - walkable mode for the CCT.
			/// </summary>
			property ControllerNonWalkableMode NonWalkableMode
			{
				ControllerNonWalkableMode get();
				void set(ControllerNonWalkableMode value);
			}

			/// <summary>
			/// Retrieve the contact offset.
			/// </summary>
			property float ContactOffset
			{
				float get();
			}

			/// <summary>
			/// Gets or sets the 'up' direction.
			/// </summary>
			property Vector3 UpDirection
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Retrieve the slope limit.
			/// </summary>
			property float SlopeLimit
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the type of controller.
			/// </summary>
			property ControllerShapeType Type
			{
				ControllerShapeType get();
			}

		internal:
			property PxController* UnmanagedPointer
			{
				PxController* get();
			}
	};
};