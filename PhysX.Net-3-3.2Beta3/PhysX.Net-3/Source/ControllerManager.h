#pragma once

#include <PxControllerManager.h> 

namespace PhysX
{
	ref class Scene;
	ref class Controller;
	ref class ControllerDesc;
	ref class ObstacleContext;

	/// <summary>
	/// Manages an array of character controllers.
	/// </summary>
	public ref class ControllerManager : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxControllerManager* _manager;
			PhysX::Scene^ _scene;

			List<Controller^>^ _controllers;

		internal:
			ControllerManager(PxControllerManager* manager, PhysX::Scene^ owner);
		public:
			~ControllerManager();
		protected:
			!ControllerManager();
		public:
			property bool Disposed
			{
				virtual bool get();
			}

		public:
			/// <summary>
			/// Creates a new character controller.
			/// </summary>
			/// <param name="controllerDesc"></param>
			generic<class T>
			where T : Controller
			T CreateController(ControllerDesc^ controllerDesc);
			/// <summary>
			/// Creates a new character controller.
			/// </summary>
			/// <param name="controllerDesc"></param>
			Controller^ CreateController(ControllerDesc^ controllerDesc);

			/// <summary>
			/// Computes character-character interactions.
			/// This function is an optional helper to properly resolve interactions between characters, in
			/// case they overlap (which can happen for gameplay reasons, etc).
			/// You should call this once per frame, before your PxController::move() calls. The function will
			/// not move the characters directly, but it will compute overlap information for each character
			/// that will be used in the next move() call.
			/// You need to provide a proper time value here so that interactions are resolved in a way that do
			/// not depend on the framerate.
			/// If you only have one character in the scene, or if you can guarantee your characters will never
			/// overlap, then you do not need to call this function.
			/// </summary>
			/// <param name="elapsedTime">Elapsed time since last call.</param>
			void ComputeInteractions(TimeSpan elapsedTime);

			//RenderBuffer^ GetRenderBuffer();

			/// <summary>
			/// Creates an obstacle context.
			/// </summary>
			ObstacleContext^ CreateObstacleContext();

			//

			/// <summary>Gets the parent scene object.</summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Gets the collection of controller.
			/// </summary>
			property IEnumerable<Controller^>^ Controllers
			{
				IEnumerable<Controller^>^ get();
			}

			/// <summary>
			/// Gets the collection of obstacle contexts.
			/// </summary>
			property IEnumerable<ObstacleContext^>^ ObstacleContexts
			{
				IEnumerable<ObstacleContext^>^ get();
			}

			/// <summary></summary>
			property Object^ UserData;

		internal:
			property PxControllerManager* UnmanagedPointer
			{
				PxControllerManager* get();
			}
	};
};