#pragma once


namespace PhysX
{
	ref class ControllerShapeHit;
	ref class ControllersHit;
	ref class UserControllerHitReport;
	ref class ControllerObstacleHit;

	class InternalUserControllerHitReport : public PxUserControllerHitReport
	{
		private:
			gcroot<UserControllerHitReport^> _hitReport;

		public:
			InternalUserControllerHitReport(UserControllerHitReport^ hitReport);

			void onShapeHit(const PxControllerShapeHit &hit);
			void onControllerHit(const PxControllersHit &hit);
			void onObstacleHit (const PxControllerObstacleHit &hit);
	};

	/// <summary>
	/// User callback class for character controller events.
	/// </summary>
	/// <remarks>
	/// Character controller hit reports are only generated when move is called.
	/// </remarks>
	public ref class UserControllerHitReport abstract
	{
		private:
			InternalUserControllerHitReport* _hitReport;

		protected:
			UserControllerHitReport();
		public:
			~UserControllerHitReport();
		protected:
			!UserControllerHitReport();

		public:
			/// <summary>
			/// Called when current controller hits a shape.
			/// </summary>
			virtual void OnShapeHit(ControllerShapeHit^ hit) abstract;

			/// <summary>
			/// Called when current controller hits another controller.
			/// </summary>
			virtual void OnControllerHit(ControllersHit^ hit) abstract;

			/// <summary>
			/// Called when current controller hits a user-defined obstacle.
			/// </summary>
			virtual void OnObstacleHit(ControllerObstacleHit^ hit) abstract;

		internal:
			property InternalUserControllerHitReport* UnmanagedPointer
			{
				InternalUserControllerHitReport* get();
			}
	};
};