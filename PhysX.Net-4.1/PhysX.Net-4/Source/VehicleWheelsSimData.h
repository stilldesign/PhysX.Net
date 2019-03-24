#pragma once


namespace PhysX
{
	ref class VehicleSuspensionData;
	ref class VehicleWheelData;
	ref class VehicleTireData;
	ref class VehicleTireLoadFilterData;
	ref class VehicleAntiRollBarData;

	/// <summary>
	/// Data structure describing configuration data of a vehicle with up to 20 wheels.
	/// </summary>
	public ref class VehicleWheelsSimData
	{
	private:
		PxVehicleWheelsSimData* _data;
	
	public:
		//VehicleWheelsSimData(PxVehicleWheelsSimData* data);
		VehicleWheelsSimData(int numberOfWheels);

		void SetChassisMass(float chassisMass);

		void CopyWheelData(VehicleWheelsSimData^ sourceData, int sourceWheelIndex, int targetWheelIndex);

		VehicleSuspensionData^ GetSuspensionData(int id);
		void SetSuspensionData(int id, VehicleSuspensionData^ data);

		VehicleWheelData^ GetWheelData(int id);
		void SetWheelData(int id, VehicleWheelData^ data);

		VehicleTireData^ GetTireData(int id);
		void SetTireData(int id, VehicleTireData^ data);

		Vector3 GetSuspensionTravelDirection(int id);
		void SetSuspensionTravelDirection(int id, Vector3 direction);

		Vector3 GetSuspensionForceApplicationPointOffset(int id);
		void SetSuspensionForceApplicationPointOffset(int id, Vector3 offset);

		Vector3 GetTireForceApplicationPointOffset(int id);
		void SetTireForceApplicationPointOffset(int id, Vector3 offset);

		Vector3 GetWheelCentreOffset(int id);
		void SetWheelCentreOffset(int id, Vector3 offset);

		VehicleTireLoadFilterData^ GetTireLoadFilterData();
		void SetTireLoadFilterData(VehicleTireLoadFilterData^ filterData);

		void DisableWheel(int wheel);

		bool IsWheelDisabled(int wheel);

		int GetWheelShapeMapping(int wheelId);
		void SetWheelShapeMapping(int wheelId, int shapeId);

		int AddAntiRollBarData(VehicleAntiRollBarData^ data);
		VehicleAntiRollBarData^ GetAntiRollBarData(int antiRollBarId);
		void GetAntiRollBarData(int antiRollBarId, VehicleAntiRollBarData^ data);
		property int NumberOfAntiRollBars
		{
			int get();
		}

		property int NumberOfWheels
		{
			int get();
		}

		//

		property PxVehicleWheelsSimData* UnmanagedPointer
		{
			PxVehicleWheelsSimData* get();
		}
	};
};