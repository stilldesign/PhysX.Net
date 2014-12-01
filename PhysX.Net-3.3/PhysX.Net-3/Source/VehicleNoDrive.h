#pragma once

#include "VehicleWheels.h"

namespace PhysX
{
	ref class VehicleWheelsSimData;

	public ref class VehicleNoDrive : VehicleWheels
	{
	private:

	internal:
		VehicleNoDrive(PxVehicleNoDrive* noDrive, PhysX::Physics^ owner);

	public:
		//VehicleNoDrive(int numberOfWheels, PhysX::Physics^ owner);
		VehicleNoDrive(PhysX::Physics^ physics, RigidDynamic^ vehicleActor, VehicleWheelsSimData^ wheelsData);

	private:
		//PxVehicleNoDrive* Create(int numberOfWheels);
		PxVehicleNoDrive* Create(PhysX::Physics^ physics, RigidDynamic^ vehicleActor, VehicleWheelsSimData^ wheelsData);

	public:
		void Setup(PhysX::Physics^ physics, RigidDynamic^ vehicleActor, VehicleWheelsSimData^ wheelsData);
		void SetToRestState();

		float GetBrakeTorque(int id);
		void SetBrakeTorque(int id, float brakeTorque);

		float GetDriveTorque(int id);
		void SetDriveTorque(int id, float driveTorque);

		float GetSteerAngle(int id);
		void SetSteerAngle(int id, float steerAngle);

		//void ExportExtraData(SerializationContext^ context);
		//void ImportExtraData(SerializationContext^ context);

		property int SteeringAngleCount
		{
			int get();
		}
		property int DriveTorqueCount
		{
			int get();
		}
		property int BrakeTorqueCount
		{
			int get();
		}

	internal:
		property PxVehicleNoDrive* UnmanagedPointer
		{
			PxVehicleNoDrive* get() new;
		}
	};
};