#pragma once

#include <PxActor.h>
#include <PxVehicle.h>

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class Vehicle4W : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxVehicle4W* _vehicle;

			Vehicle4W(PxVehicle4W* vehicle);
		public:
			~Vehicle4W();
		protected:
			!Vehicle4W();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Autogear flag used by vehicle simulation.
			/// </summary>
			property bool UseAutoGears
			{
				bool get();
				void set(bool value);
			}

			/// <summary>
			/// Gearup digital control value used by vehicle simulation.
			/// </summary>
			property bool GearUpPressed
			{
				bool get();
				void set(bool value);
			}

			/// <summary>
			/// Geardown digital control value used by vehicle simulation.
			/// </summary>
			property bool GearDownPressed
			{
				bool get();
				void set(bool value);
			}

			/// <summary>
			/// Current gear.
			/// </summary>
			property int CurrentGear
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Target gear (different from current gear if a gear change is underway).
			/// </summary>
			property int TargetGear
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Rotation speeds of wheels and engine.
			/// </summary>
			property array<float>^ InternalDynamics
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Timers used to trigger sticky friction to hold the car perfectly at rest.
			/// </summary>
			property array<float>^ TyreLowForwardSpeedTimers
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Reported rotation angle about rolling axis.
			/// </summary>
			property array<float>^ WheelRotationAngles
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Reported compression of each suspension spring.
			/// </summary>
			property array<float>^ SuspensionJounces
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Reported longitudinal slip of each tyre.
			/// </summary>
			property array<float>^ LongitudinalSlips
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Reported lateral slip of each tyre.
			/// </summary>
			property array<float>^ LaterialSlips
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Reported friction experienced by each tyre.
			/// </summary>
			property array<float>^ TypeFrictions
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Reported surface type experienced by each tyre.
			/// </summary>
			property array<int>^ TyreSurfaceTypes
			{
				array<int>^ get();
				void set(array<int>^ value);
			}

			/// <summary>
			/// Reported start point of suspension line raycasts used in more recent scene query.
			/// </summary>
			property array<Vector3>^ SuspensionLineStarts
			{
				array<Vector3>^ get();
				void set(array<Vector3>^ value);
			}

			/// <summary>
			/// Reported directions of suspension line raycasts used in more recent scene query.
			/// </summary>
			property array<Vector3>^ SuspensionLineDirections
			{
				array<Vector3>^ get();
				void set(array<Vector3>^ value);
			}

			/// <summary>
			/// Reported lengths of suspension line raycasts used in more recent scene query.
			/// </summary>
			property array<float>^ SuspensionLineLengths
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Reported time that has passed since gear change started.
			/// </summary>
			property float GearSwitchTime
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Reported time that has passed since last autobox gearup/geardown decision.
			/// </summary>
			property float AutoBoxSwitchTime
			{
				float get();
				void set(float value);
			}

		internal:
			property PxVehicle4W* UnmanagedPointer
			{
				PxVehicle4W* get();
			}
	};
};