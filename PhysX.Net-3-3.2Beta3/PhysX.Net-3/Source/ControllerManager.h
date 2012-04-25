#pragma once

#include <PxControllerManager.h> 

namespace PhysX
{
	ref class Scene;
	ref class Controller;
	ref class ControllerDesc;

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

			/// <summary>Updates the exposed position from the filtered position of all controllers.</summary>
			void UpdateControllers();

			//RenderBuffer^ GetRenderBuffer();

			//

			/// <summary>Gets the parent scene object.</summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>Gets the Collection of Controller</summary>
			property IEnumerable<Controller^>^ Controllers
			{
				IEnumerable<Controller^>^ get();
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