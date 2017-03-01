#pragma once


namespace PhysX
{
	public ref class VehicleAutoBoxData
	{
		internal:
			static VehicleAutoBoxData^ ToManaged(PxVehicleAutoBoxData data);
			static PxVehicleAutoBoxData ToUnmanaged(VehicleAutoBoxData^ data);

		public:
			/// <summary>
			/// Value of engineRevs/maxEngineRevs that is high enough to increment gear. Range: (0, 1).
			/// </summary>
			property array<float>^ UpRatios;
			/// <summary>
			/// Value of engineRevs/maxEngineRevs that is low enough to decrement gear. Range: (0, 1).
			/// </summary>
			property array<float>^ DownRatios;
	};
};