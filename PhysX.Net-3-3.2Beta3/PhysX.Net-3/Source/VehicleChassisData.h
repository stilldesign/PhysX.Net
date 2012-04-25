#pragma once

#include <PxVehicle.h>

namespace PhysX
{
	private ref class VehicleChassisData
	{
		internal:
			static PxVehicleChassisData ToUnmanaged(VehicleChassisData^ data);
			static VehicleChassisData^ ToManaged(PxVehicleChassisData data);

		public:
			property Vector3 MOI;
			property float Mass;
			property Vector3 CMOffset;
	};
};