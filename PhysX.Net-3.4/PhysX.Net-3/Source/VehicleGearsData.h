#pragma once


namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleGearsData
	{
		public:
			static const int MaximumNumberOfGearRatios = PxVehicleGearsData::eGEARSRATIO_COUNT;

			VehicleGearsData();

		internal:
			static PxVehicleGearsData ToUnmanaged(VehicleGearsData^ gearsData);
			static VehicleGearsData^ ToManaged(PxVehicleGearsData gearsData);

		public:
			/// <summary>
			/// Gear ratios Range: (0, inf).
			/// </summary>
			property array<float>^ Ratios;

			/// <summary>
			/// Gear ratio applied is Ratios[currentGear]*finalRatio Range: (0, inf).
			/// </summary>
			property float FinalRatio;

			/// <summary>
			/// Number of gears (including reverse and neutral). Range: (0, VehicleEngineData.MaximumNumberOfGearRatios).
			/// </summary>
			property int NumberOfRatios;

			/// <summary>
			/// Time it takes to switch gear, specified in s. Range: (0, VehicleEngineData.MaximumNumberOfGearRatios)
			/// </summary>
			property float SwitchTime;
	};
};