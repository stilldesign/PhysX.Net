#pragma once

#include "VehicleEnum.h"

namespace PhysX
{
	ref class Physics;
	ref class VehicleWheelsSimData;
	ref class VehicleDriveSimData4W;
	ref class BatchQuery;
	ref class VehicleWheels;
	ref class RaycastQueryResult;
	ref class VehicleWheelsDynData;
	ref class VehicleConcurrentUpdateData;

	public ref class VehicleSDK : IDisposable
	{
	public:
		/// <summary>Raised before any disposing is performed.</summary>
		virtual event EventHandler^ OnDisposing;
		/// <summary>Raised once all disposing is performed.</summary>
		virtual event EventHandler^ OnDisposed;

	private:
		Physics^ _physics;

		bool _initalized;

	internal:
		VehicleSDK(PhysX::Physics^ physics);
	public:
		~VehicleSDK();
	protected:
		!VehicleSDK();
	public:
		property bool Disposed
		{
			virtual bool get();
		}

	private:
		void EnsureInitalized();

	public:
		bool Initalize();
		void Close();

		/// <summary>
		/// Enable 4W vehicle sim data as a 3W car with tadpole config (2 front wheels, 1 rear wheel).
		/// The rear-left wheel is removed and the rear-right wheel is positioned at the centre of the rear axle.
		/// The suspension of the rear-right wheel is modified to support the entire mass of the front car while
		/// preserving its natural frequency and damping ratio.
		/// </summary>
		void Vehicle4WEnable3WDeltaMode(VehicleWheelsSimData^ suspensionWheelTireData, VehicleWheelsDynData^ wheelsDynData, VehicleDriveSimData4W^ coreData);

		/// <summary>
		/// Enable 4W vehicle sim data as a 3W car with tadpole config (2 front wheels, 1 rear wheel).
		/// The rear-left wheel is removed and the rear-right wheel is positioned at the centre of the
		/// rear axle. The suspension of the rear-right wheel is modified to support the entire mass of
		/// the front car while preserving its natural frequency and damping ratio.
		void Vehicle4WEnable3WTadpoleMode(VehicleWheelsSimData^ suspWheelTireData, VehicleWheelsDynData^ wheelsDynData, VehicleDriveSimData4W^ coreData);

		/// <summary>
		/// Default implementation of PxVehicleComputeTireForce.
		/// </summary>
		void VehicleComputeTireForceDefault(float tireFriction, float longSlip, float latSlip, float camber,
			float wheelOmega, float wheelRadius, float recipWheelRadius, float restTireLoad, float normalisedTireLoad,
			float tireLoad, float gravity, float recipGravity, float wheelTorque, float tireLongForceMag,
			float tireLatForceMag, float tireAlignMoment);

		//void PxVehicleDrive4WSmoothAnalogRawInputsAndSetAnalogInputs  ( const PxVehiclePadSmoothingData &  padSmoothing,  
		//const PxFixedSizeLookupTable< 8 > &  steerVsForwardSpeedTable,  
		//const PxVehicleDrive4WRawInputData &  rawInputData,  
		//const PxReal  timestep,  
		//PxVehicleDrive4W &  focusVehicle)

		//	void PxVehicleDrive4WSmoothDigitalRawInputsAndSetAnalogInputs  ( const PxVehicleKeySmoothingData &  keySmoothing,  
		//  const PxFixedSizeLookupTable< 8 > &  steerVsForwardSpeedTable,  
		//  const PxVehicleDrive4WRawInputData &  rawInputData,  
		//  const PxReal  timestep,  
		//  PxVehicleDrive4W &  focusVehicle   
		// )    
		//
		//Used to smooth and set analog vehicle control values (accel,brake,handbrake,steer) from digital inputs (keyboard). Also used to set boolean gearup, geardown values. 
		//
		//
		//
		//void PxVehicleDriveTankSmoothAnalogRawInputsAndSetAnalogInputs  ( const PxVehiclePadSmoothingData &  padSmoothing,  
		//  const PxVehicleDriveTankRawInputData &  rawInputData,  
		//  const PxReal  timestep,  
		//  PxVehicleDriveTank &  focusVehicle   
		// )    
		//
		//Used to smooth and set analog tank control values from analog inputs (gamepad). Also used to set boolean gearup, geardown values. 
		//
		//
		//
		//void PxVehicleDriveTankSmoothDigitalRawInputsAndSetAnalogInputs  ( const PxVehicleKeySmoothingData &  padSmoothing,  
		//  const PxVehicleDriveTankRawInputData &  rawInputData,  
		//  const PxReal  timestep,  
		//  PxVehicleDriveTank &  focusVehicle   
		// )

		void VehicleSetBasisVectors(Vector3 up, Vector3 forward);

		// TODO: Add vehiclesToRaycast arg
		void VehicleSuspensionRaycasts(BatchQuery^ batchQuery, array<VehicleWheels^>^ vehicles, array<RaycastQueryResult^>^ sceneQueryResults);
		
		//void PxVehicleUpdates(float timestep, Vector3 gravity, VehicleDrivableSurfaceToTireFrictionPairs vehicleDrivableSurfaceToTireFrictionPairs, int numVehicles, array<VehicleWheels^>^ vehicles);

		//void VehiclePostUpdates(VehicleConcurrentUpdateData^ concurrentUpdateData, array<VehicleWheels^>^ vehicles);

		/// <summary>
		/// Reconfigure the vehicle to reflect a new center of mass local pose that has been applied to the actor.
		/// The function requires(i) the center of mass local pose that was last used to configure the vehicle and
		/// the vehicle's actor, (ii) the new center of mass local pose that has been applied to the vehicle's actor
		/// and will now be applied to the vehicle, and(iii) the direction of gravity(0 for x - axis, 1 for y - axis, 2 for z - axis).
		/// </summary>
		VehicleWheels^ VehicleUpdateCMassLocalPose(Matrix oldCMassLocalPose, Matrix newCMassLocalPose, VehicleGravityDirection gravityDirection, VehicleWheels^ vehicle);

		//

		property PhysX::Physics^ Physics
		{
			PhysX::Physics^ get();
		}
	};
};