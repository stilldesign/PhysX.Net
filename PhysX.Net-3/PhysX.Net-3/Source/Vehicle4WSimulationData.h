#pragma once

#include "VehicleWheelValues.h"
#include <PxVehicle.h> 

namespace PhysX
{
	ref class VehicleSuspensionData;
	ref class VehicleChassisData;
	ref class VehicleEngineData;
	ref class VehicleGearsData;
	ref class VehicleClutchData;
	ref class VehicleAutoBoxData;
	ref class VehicleDifferential4WData;
	ref class VehicleWheelData;
	ref class VehicleTyreData;
	ref class VehicleTyreLoadFilterData;

	public ref class Vehicle4WSimulationData
	{
		public:
			literal int NumberOfWheels = PxVehicle4WSimulationData::eNUM_WHEELS;

			Vehicle4WSimulationData();

		internal:
			static PxVehicle4WSimulationData ToUnmanaged(Vehicle4WSimulationData^ data);
			static Vehicle4WSimulationData^ ToManaged(PxVehicle4WSimulationData data);

			//

		public:
			property VehicleChassisData^ ChassisData;

			property VehicleEngineData^ EngineData;

			property VehicleGearsData^ GearsData;

			property VehicleClutchData^ ClutchData;

			property VehicleAutoBoxData^ AutoBoxData;

			property VehicleDifferential4WData^ DifferentialData;

			property VehicleWheelValues<VehicleSuspensionData^>^ SuspensionData;

			property VehicleWheelValues<VehicleWheelData^>^ WheelData;

			property VehicleWheelValues<VehicleTyreData^>^ TyreData;

			property VehicleWheelValues<Vector3>^ SuspensionTravelDirections;

			property VehicleWheelValues<Vector3>^ SuspensionForceApplicationPointOffsets;

			property VehicleWheelValues<Vector3>^ TyreForceApplicationPointOffsets;

			property VehicleWheelValues<Vector3>^ WheelCentreOffsets;

			property VehicleTyreLoadFilterData^ TyreLoadFilterData;

			property VehicleWheelValues<float>^ TyreRestLoads;

			property VehicleWheelValues<float>^ ReciprocalTyreRestLoads;

			property float AckermannAccuracy;
	};
};