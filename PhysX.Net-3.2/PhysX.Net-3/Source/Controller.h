#pragma once

#include <PxController.h>
#include "CharacterEnum.h"

namespace PhysX
{
	ref class ControllerManager;
	ref class ControllerFilters;
	ref class ObstacleContext;

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

			void Move(Vector3 displacement, TimeSpan elapsedTime);
			void Move(Vector3 displacement, TimeSpan elapsedTime, float minimumDistance, ControllerFilters^ filters, [Optional] ObstacleContext^ obstacles);

			/// <summary>
			/// The character controller uses caching in order to speed up collision testing, this caching
			/// can not detect when static objects have changed in the scene. You need to call this method
			/// when such changes have been made. 
			/// </summary>
			void ReportSceneChanged();

			//

			/// <summary>
			/// Gets the associated controller manager instance.
			/// </summary>
			property PhysX::ControllerManager^ ControllerManager
			{
				PhysX::ControllerManager^ get();
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
			/// Gets or sets the step height.
			/// </summary>
			property float StepOffset
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Sets the interaction mode for the CCT.
			/// </summary>
			property CCTInteractionMode Interaction
			{
				CCTInteractionMode get();
				void set(CCTInteractionMode value);
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
			}

			/// <summary>
			/// Gets or sets the user data associated with this controller.
			/// </summary>
			property Object^ UserData;

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