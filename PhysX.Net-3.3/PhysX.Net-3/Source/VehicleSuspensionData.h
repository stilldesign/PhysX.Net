#pragma once

//#include <PxVehicleComponents.h> 

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

			/// <summary>
			/// Camber angle (in radians) of wheel when the suspension is at its rest
			/// position, specified in radians. Range: [-pi / 2, pi / 2].
			/// </summary>
			property float CamberAtRest;

			/// <summary>
			/// Camber angle (in radians) of wheel when the suspension is at maximum compression.
			/// For compressed suspensions the camber angle is a linear interpolation of CamberAngleAtRest and CamberAtMaxCompression.
			/// Specified in radians.
			/// Range: [-pi / 2, pi / 2]
			/// </summary>
			property float CamberAtMaxCompression;

			/// <summary>
			/// Camber angle (in radians) of wheel when the suspension is at maximum droop.
			/// For extended suspensions the camber angle is linearly interpolation of CamberAngleAtRest and CamberAtMaxDroop.
			/// Specified in radians.
			/// Range: [-pi / 2, pi / 2]
			/// </summary>
			property float CamberAtMaxDroop;
	};
};