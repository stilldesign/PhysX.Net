#pragma once

namespace PhysX
{
	interface class IVehicleComputeTireForceInput;
	interface class IVehicleComputeTireForceOutput;

	public ref class VehicleWheelsDynData
	{
	public:
		void SetToRestState();

		/// <summary>
		/// Set the tire force shader function.
		/// </summary>
		void SetTireForceShaderFunction(IVehicleComputeTireForceInput^ input, IVehicleComputeTireForceOutput^ output);
	};
}