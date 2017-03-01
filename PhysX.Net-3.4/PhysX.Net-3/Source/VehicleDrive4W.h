#pragma once

#include "VehicleDrive.h"
#include "VehicleDifferential4WData.h"
#include "VehicleAckermannGeometryData.h"
#include "VehicleDriveSimData4W.h"
#include "VehicleWheelsSimData.h"

namespace PhysX
{
	public ref class VehicleDrive4W : VehicleDrive
	{
	private:
		VehicleDriveSimData4W^ _simData;

	public:
		VehicleDrive4W(PhysX::Physics^ physics, RigidDynamic^ actor, VehicleWheelsSimData^ wheelsData, VehicleDriveSimData4W^ driveData, int numNonDrivenWheels);

	private:
		static PxVehicleDrive4W* Create(PhysX::Physics^ physics, RigidDynamic^ actor, VehicleWheelsSimData^ wheelsData, VehicleDriveSimData4W^ driveData, int numNonDrivenWheels);
		
	public:
		property VehicleDriveSimData4W^ DriveSimData
		{
			VehicleDriveSimData4W^ get();
		}
		
	internal:
		property PxVehicleDrive4W* UnmanagedPointer
		{
			PxVehicleDrive4W* get();
		}
	};
};