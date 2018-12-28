#pragma once


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

			/// <summary>
			/// Enables or disables the overlap recovery module. 
			/// The overlap recovery module can be used to depenetrate CCTs from static objects when an overlap is detected. This can happen in three main cases:
			/// 
			/// when the CCT is directly spawned or teleported in another object
			/// when the CCT algorithm fails due to limited FPU accuracy
			/// when the "up vector" is modified, making the rotated CCT shape overlap surrounding objects
			/// When activated, the CCT module will automatically try to resolve the penetration, and move the CCT to a safe place where it does not overlap other objects anymore. This only concerns static objects, dynamic objects are ignored by the recovery module.
			/// 
			/// When the recovery module is not activated, it is possible for the CCTs to go through static objects. By default, the recovery module is enabled.
			/// 
			/// The recovery module currently works with all geometries except heightfields.
			/// </summary>
			void SetOverlapRecoveryModule(bool flag);

			/// <summary>
			/// Shift the origin of the character controllers and obstacle objects by the specified vector. 
			/// The positions of all character controllers, obstacle objects and the corresponding data
			/// structures will get adjusted to reflect the shifted origin location (the shift vector will get
			/// subtracted from all character controller and obstacle object positions).
			/// Note:
			/// It is the user's responsibility to keep track of the summed total origin shift and adjust
			/// all input/output to/from PhysXCharacterKinematic accordingly.
			/// This call will not automatically shift the PhysX scene and its objects. You need to call
			/// Scene.ShiftOrigin() seperately to keep the systems in sync.
			/// </summary>
			void ShiftOrigin(Vector3 shift);

			/// <summary>
			/// Enables or disables vertical sliding against ceilings.
			/// Geometry is seen as "ceilings" when the following condition is met :
			///		dot product(contact normal, up direction)<0.0f
			/// 	This flag controls whether characters should slide vertically along the geometry in that case.
			/// By default, sliding is allowed.
			/// </summary>
			void SetPreventVerticalSlidingAgainstCeiling(bool flag);

			//

			/// <summary>Gets the parent scene object.</summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Gets the collection of controller.
			/// </summary>
			property IReadOnlyList<Controller^>^ Controllers
			{
				IReadOnlyList<Controller^>^ get();
			}

			/// <summary>
			/// Gets the collection of obstacle contexts.
			/// </summary>
			property array<ObstacleContext^>^ ObstacleContexts
			{
				array<ObstacleContext^>^ get();
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