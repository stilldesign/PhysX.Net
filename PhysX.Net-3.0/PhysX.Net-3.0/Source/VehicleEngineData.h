#pragma once

#include "VehicleEnum.h"
#include <PxVehicle.h>

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleEngineData
	{
		public:
			static const int MaximumNumberOfEngineTorqueCurveEntries = PxVehicleEngineData::eMAX_NUM_ENGINE_TORQUE_CURVE_ENTRIES;
		
		internal:
			static PxVehicleEngineData ToUnmanaged(VehicleEngineData^ data);
			static VehicleEngineData^ ToManaged(PxVehicleEngineData data);

		public:
			/// <summary>
			/// Maximum torque available to apply to the engine, specified in Nm. Range: (0, inf).
			/// </summary>
			property float PeakTorque;

			/// <summary>
			/// Maximum rotation speed of the engine, specified in radians per second. Range: (0, inf).
			/// </summary>
			property float MaxOmega;

			/// <summary>
			/// Damping rate of engine when the clutch is engaged, specified in s^-1. Range: (0, inf).
			/// </summary>
			property float EngagedClutchDampingRate;

			/// <summary>
			/// Damping rate of engine when the clutch is not engaged, specified in s^-1. Range: (0, inf).
			/// </summary>
			property float DisengagedClutchDampingRate;
	};
};