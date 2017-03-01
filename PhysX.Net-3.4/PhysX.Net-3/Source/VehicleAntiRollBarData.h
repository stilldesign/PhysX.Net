#pragma once

namespace physx
{
	class PxVehicleAntiRollBarData;
}

namespace PhysX
{
	public ref class VehicleAntiRollBarData
	{
	internal:
		static PxVehicleAntiRollBarData ToUnmanaged(VehicleAntiRollBarData^ managed);
		static VehicleAntiRollBarData^ ToManaged(PxVehicleAntiRollBarData unmanaged);

	public:
		property int Wheel0;
		property int Wheel1;
		property float Stiffness;
	};
}