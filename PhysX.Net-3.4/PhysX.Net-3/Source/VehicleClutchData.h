#pragma once


namespace PhysX
{
	public ref class VehicleClutchData
	{
		internal:
			static VehicleClutchData^ ToManaged(PxVehicleClutchData data);
			static PxVehicleClutchData ToUnmanaged(VehicleClutchData^ data);

		public:
			/// <summary>
			/// Strength of clutch Range: (0, VehicleGearsData.MaximumNumberOfGearRatios).
			/// </summary>
			property float Strength;
	};
};