#pragma once

#include "VehicleEnum.h"

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleEngineData
	{
		public:
			literal int MaximumNumberOfEngineTorqueCurveEntries = PxVehicleEngineData::eMAX_NB_ENGINE_TORQUE_CURVE_ENTRIES;
		
		internal:
			static PxVehicleEngineData ToUnmanaged(VehicleEngineData^ data);
			static VehicleEngineData^ ToManaged(PxVehicleEngineData data);

		public: static VehicleEngineData^ TestManagedUnmanagedConversion(VehicleEngineData^ data)
			{
				return ToManaged(ToUnmanaged(data));
			}

		public:
			// TODO: TorqueCurve property

			/// <summary>
			/// Gets or sets the maximum torque available to apply to the engine, specified in Nm. Range: (0, inf).
			/// </summary>
			property float PeakTorque;

			/// <summary>
			/// Gets or sets the maximum rotation speed of the engine, specified in radians per second. Range: (0, inf).
			/// </summary>
			property float MaxOmega;

			/// <summary>
			/// Damping rate of engine in s^-1 when full throttle is applied. Damping rate applied at run-time is an interpolation between mDampingRateZeroThrottleClutchEngaged and mDampingRateFullThrottle if the clutch is engaged. If the clutch is disengaged (in neutral gear) the damping rate applied at run-time is an interpolation between mDampingRateZeroThrottleClutchDisengaged and mDampingRateFullThrottle. Range: (0,inf).
			/// </summary>
			property float DampingRateFullThrottle;

			/// <summary>
			/// Damping rate of engine in s^-1 at zero throttle when the clutch is engaged. Damping rate applied at run-time is an interpolation between mDampingRateZeroThrottleClutchEngaged and mDampingRateFullThrottle if the clutch is engaged. If the clutch is disengaged (in neutral gear) the damping rate applied at run-time is an interpolation between mDampingRateZeroThrottleClutchDisengaged and mDampingRateFullThrottle. Range: (0,inf).
			/// </summary>
			property float DampingRateZeroThrottleClutchEngaged;

			/// <summary>
			/// Damping rate of engine in s^-1 at zero throttle when the clutch is disengaged (in neutral gear). Damping rate applied at run-time is an interpolation between mDampingRateZeroThrottleClutchEngaged and mDampingRateFullThrottle if the clutch is engaged. If the clutch is disengaged (in neutral gear) the damping rate applied at run-time is an interpolation between mDampingRateZeroThrottleClutchDisengaged and mDampingRateFullThrottle. Range: (0,inf).
			/// </summary>
			property float DampingRateZeroThrottleClutchDisengaged;
	};
};