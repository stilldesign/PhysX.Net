#pragma once

#include "VehicleWheels.h"
#include "VehicleDriveDynData.h"

namespace PhysX
{
	public ref class VehicleDrive : VehicleWheels
	{
	private:
		VehicleDriveDynData^ _driveDynData;

	protected:
		VehicleDrive(PxVehicleDrive* drive, PhysX::Physics^ owner);

	public:
		/// <summary>
		/// Dynamics data of vehicle instance.
		/// </summary>
		property VehicleDriveDynData^ DriveDynData
		{
			VehicleDriveDynData^ get();
		}
	};
};