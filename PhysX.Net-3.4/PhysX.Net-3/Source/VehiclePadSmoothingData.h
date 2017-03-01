#pragma once


namespace PhysX
{
	/// <summary>
	/// Used to produce smooth analog driving control values from analog inputs.
	/// </summary>
	public ref class VehiclePadSmoothingData
	{
		public:
			static const int MaximumNumberOfVehicleAnalogInputs = PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS;

		internal:
			static VehiclePadSmoothingData^ ToManaged(PxVehiclePadSmoothingData desc);
			static PxVehiclePadSmoothingData ToUnmanaged(VehiclePadSmoothingData^ desc);

		public:
			/// <summary>
			/// Rise rate of each analog value if digital value is 1.
			/// </summary>
			property array<float>^ RiseRates;

			/// <summary>
			/// Fall rate of each analog value if digital value is 0.
			/// </summary>
			property array<float>^ FallRates;
	};
};