#pragma once

#include "VehicleDriveSimData.h"

namespace PhysX
{
	ref class VehicleDifferential4WData;
	ref class VehicleAckermannGeometryData;

	public ref class VehicleDriveSimData4W : VehicleDriveSimData
	{
	public:
		VehicleDriveSimData4W();
	private:
		static PxVehicleDriveSimData4W* Create();
	internal:
		VehicleDriveSimData4W(PxVehicleDriveSimData4W* simData);

	public:
		VehicleDifferential4WData^ GetDifferentialData();
		void SetDifferentialData(VehicleDifferential4WData^ data);

		VehicleAckermannGeometryData^ GetAckermannGeometryData();
		void SetAckermannGeometryData(VehicleAckermannGeometryData^ data);

	internal:
		property PxVehicleDriveSimData4W* UnmanagedPointer
		{
			PxVehicleDriveSimData4W* get();
		}
	};
};