#pragma once


namespace PhysX
{
	public ref class VehicleSuspensionData
	{
		internal:
			static PxVehicleSuspensionData ToUnmanaged(VehicleSuspensionData^ data);
			static VehicleSuspensionData^ ToManaged(PxVehicleSuspensionData data);

		public:
			/// <summary>
			/// Spring strength of suspension unit, specified in N m^-1. Range: (0, inf).
			/// </summary>
			property float SpringStrength;

			/// <summary>
			/// Spring damper rate of suspension unit, specified in s^-1. Range: (0, inf).
			/// </summary>
			property float SpringDamperRate;

			/// <summary>
			/// Maximum compression allowed by suspension spring, specified in m. Range: (0, inf).
			/// </summary>
			property float MaxCompression;

			/// <summary>
			/// Maximum elongation allowed by suspension spring, specified in m. Range: (0, inf).
			/// </summary>
			property float MaxDroop;

			/// <summary>
			/// Mass of vehicle that is supported by suspension spring, specified in kg. Range: (0, inf).
			/// </summary>
			property float SprungMass;
	};
};