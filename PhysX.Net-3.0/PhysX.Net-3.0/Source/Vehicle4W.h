#pragma once

#include "FilterData.h"
#include <PxActor.h>
#include <PxVehicle.h>
#include <PxVehicleUtils.h>

namespace PhysX
{
	ref class Physics;
	ref class Vehicle4WSetupDesc;
	ref class VehicleSuspensionRaycastResult;
	ref class Shape;

	/// <summary>
	/// 
	/// </summary>
	public ref class Vehicle4W : IDisposable
	{
		public:
			const literal int MaximumNumberOfChassisShapes = PX_MAX_NUM_CHASSIS_SHAPES;

		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxVehicle4W* _vehicle;
			PhysX::Physics^ _physics;

		internal:
			Vehicle4W(PxVehicle4W* vehicle, PhysX::Physics^ owner);
		public:
			~Vehicle4W();
		protected:
			!Vehicle4W();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			//

			static void Initalize(PhysX::Physics^ physics);

			/// <summary>
			/// Creates a Vehicle4W.
			/// </summary>
			/// <param name="description">A description of the vehicle to create.</param>
			static Vehicle4W^ Setup(Vehicle4WSetupDesc^ description);

			///**
			//\brief Start raycasts of all suspension lines.
			//\brief sceneQueryResults array must have dimensions [numVehicles*PxVehicleSimulationData::eNUM_WHEELS] or greater.
			//*/
			//void PxVehicle4WSuspensionRaycasts(PxBatchQuery* batchQuery, const PxU32 numVehicles, PxRaycastQueryResult* sceneQueryResults, PxVehicle4W** vehicles);

			///**
			//\brief Update an array of vehicles.
			//*/
			//void PxVehicle4WUpdate(const PxReal timestep, const PxVec3& gravity, const PxVehicleDrivableSurfaceToTyreFrictionPairs& vehicleDrivableSurfaceToTyreFrictionPairs, const PxU32 numVehicles, PxVehicle4W** vehicles);

			static FilterData SetupVehicleShapeQueryFilterData(int vehicleIndex);

			/// <summary>
			/// Set analog and digital inputs directly.
			/// Accel,brake,handbrake must be in range(0,1)
			/// steer must be in range (-1,1)
			/// </summary>
			/// <param name="acceleration">The acceleration.</param>
			/// <param name="brake">The brake.</param>
			/// <param name="handbrake">The handbrake.</param>
			/// <param name="steer">The steer.</param>
			/// <param name="gearup">true to gearup.</param>
			/// <param name="geardown">true to geardown.</param>
			void SetAnalogInputs(float acceleration, float brake, float handbrake, float steer, bool gearup, bool geardown);

			/// <summary>
			/// Start a gear change to a target gear.
			/// </summary>
			/// <param name="targetGear">Target gear.</param>
			void StartGearChange(int targetGear);

			/// <summary>
			/// Force an immediate gear change to a target gear.
			/// </summary>
			/// <param name="targetGear">Target gear.</param>
			void ForceGearChange(int targetGear);

			/// <summary>
			/// Set a vehicle to its rest state.
			/// Call after PxVehicle4WSetup.
			/// </summary>
			void SetToRestState();

			/// <summary>
			/// Compute the rigid body velocity component along the forward vector.
			/// </summary>
			float ComputeForwardSpeed();

			/// <summary>
			/// Compute the rigid body velocity component along the right vector.
			/// </summary>
			float ComputeSidewaysSpeed();

			/// <summary>
			/// Fill a supplied buffer with the required number of chassis collision shapes.
			/// </summary>
			array<Shape^>^ GetChassisShapes();

			/// <summary>
			/// Return the rotation speed of a specified wheel.
			/// </summary>
			/// <param name="wheelIndex">Zero-based index of the wheel.</param>
			/// <returns>The wheel rotation speed.</returns>
			float GetWheelRotationSpeed(int wheelIndex);

			/// <summary>
			/// Return the rotation angle of the specified wheel about the axis of rolling rotation.
			/// </summary>
			/// <param name="wheelIndex">Zero-based index of the wheel.</param>
			float GetWheelRotationAngle(int wheelIndex);

			/// <summary>
			/// Return the suspension jounce of the specified suspension.
			/// </summary>
			/// <param name="suspensionIndex">Zero-based index of the susp.</param>
			float GetSuspensionJounce(int suspensionIndex);

			/// <summary>
			/// Return the longitudinal slip of the specified tyre.
			/// </summary>
			/// <param name="tyreIndex">Zero-based index of the tyre.</param>
			float GetTyreLongSlip(int tyreIndex);

			/// <summary>
			/// Return the lateral slip of the specified tyre.
			/// </summary>
			/// <param name="tyreIndex">Zero-based index of the tyre.</param>
			float GetTyreLaterialSlip(int tyreIndex);

			/// <summary>Return the friction applied to the specified tyre.</summary>
			/// <param name="tyreIndex">Zero-based index of the tyre.</param>
			float GetTyreFriction(int tyreIndex);

			/// <summary>
			/// Return the drivable surface type underneath the specified tyre.
			/// </summary>
			/// <param name="tyreIndex">Zero-based index of the tyre.</param>
			int GetTyreDrivableSurfaceType(int tyreIndex);

			/// <summary>
			/// Return the raycast start, direction, and length of the specified suspension line.
			/// </summary>
			/// <param name="suspensionIndex">Zero-based index of the susp.</param>
			VehicleSuspensionRaycastResult^ GetSuspensionRaycast(int suspensionIndex);

			//

			/// <summary>
			/// Gets the parent physics object.
			/// </summary>
			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
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

			/// <summary>
			/// Return the accel applied to a vehicle.
			/// </summary>
			property float AppliedAcceleration
			{
				float get();
			}

			/// <summary>
			/// Return the brake applied to a vehicle.
			/// </summary>
			property float AppliedBrake
			{
				float get();
			}

			/// <summary>
			/// Return the handbrake applied to a vehicle.
			/// </summary>
			property float AppliedHandbrake
			{
				float get();
			}

			/// <summary>
			/// Return the steer applied to a vehicle.
			/// </summary>
			property float AppliedSteer
			{
				float get();
			}

			/// <summary>
			/// Return the gearup applied to a vehicle.
			/// </summary>
			property bool AppliedGearup
			{
				bool get();
			}

			/// <summary>
			/// Return the geardown applied to a vehicle.
			/// </summary>
			property bool AppliedGeardown
			{
				bool get();
			}

			/// <summary>
			/// Test if all wheels are off the ground.
			/// </summary>
			property bool IsInAir
			{
				bool get();
			}

			/// <summary>
			/// Return the collision shape for the front left wheel.
			/// </summary>
			property Shape^ FrontLeftWheelShape
			{
				Shape^ get();
			}

			/// <summary>
			/// Return the collision shape for the front right wheel.
			/// </summary>
			property Shape^ FrontRightWheelShape
			{
				Shape^ get();
			}

			/// <summary>
			/// Return the collision shape for the rear left wheel.
			/// </summary>
			property Shape^ RearLeftWheelShape
			{
				Shape^ get();
			}

			/// <summary>
			/// Return the collision shape for the rear right wheel.
			/// </summary>
			property Shape^ RearRightWheelShape
			{
				Shape^ get();
			}

			/// <summary>
			/// Return the number of chassis collision shapes.
			/// </summary>
			property int NumberOfChassisShapes
			{
				int get();
			}

			/// <summary>
			/// Return the rotation speed of the engine.
			/// </summary>
			property float EngineRotationSpeed
			{
				float get();
			}

		internal:
			property PxVehicle4W* UnmanagedPointer
			{
				PxVehicle4W* get();
			}
	};
};