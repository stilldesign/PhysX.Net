#pragma once


namespace PhysX
{
	/// <summary>
	/// Used to produce smooth analog driving control values from key inputs.
	/// </summary>
	public ref class VehicleKeySmoothingData
	{
		public:
			literal int MaximumNumberOfVehicleAnalogInputs = PxVehicleDriveDynData::eMAX_NB_ANALOG_INPUTS;

		internal:
			static VehicleKeySmoothingData^ ToManaged(PxVehicleKeySmoothingData desc);
			static PxVehicleKeySmoothingData ToUnmanaged(VehicleKeySmoothingData^ desc);

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