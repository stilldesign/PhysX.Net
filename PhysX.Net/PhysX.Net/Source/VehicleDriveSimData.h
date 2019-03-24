#pragma once


namespace PhysX
{
	ref class VehicleEngineData;
	ref class VehicleClutchData;
	ref class VehicleGearsData;
	ref class VehicleAutoBoxData;

	public ref class VehicleDriveSimData
	{
	private:
		PxVehicleDriveSimData* _data;

	public:
		VehicleDriveSimData();
	internal:
		VehicleDriveSimData(PxVehicleDriveSimData* data);

	public:
		VehicleEngineData^ GetEngineData();
		void SetEngineData(VehicleEngineData^ engine);

		VehicleClutchData^ GetClutchData();
		void SetClutchData(VehicleClutchData^ clutch);

		VehicleGearsData^ GetGearsData();
		void SetGearsData(VehicleGearsData^ gears);

		VehicleAutoBoxData^ GetAutoBoxData();
		void SetAutoBoxData(VehicleAutoBoxData^ autobox);

	internal:
		property PxVehicleDriveSimData* UnmanagedPointer
		{
			PxVehicleDriveSimData* get();
		}
	};
};