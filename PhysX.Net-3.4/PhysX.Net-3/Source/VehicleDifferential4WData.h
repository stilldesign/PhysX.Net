#pragma once

#include "VehicleEnum.h"

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleDifferential4WData
	{
		internal:
			static PxVehicleDifferential4WData ToUnmanaged(VehicleDifferential4WData^ data);
			static VehicleDifferential4WData^ ToManaged(PxVehicleDifferential4WData data);

		public:
			/// <summary>
			/// Ratio of torque split between front and rear (>0.5 means more to front, <0.5 means more to rear).
			/// </summary>
			property float FrontRearSplit;
			/// <summary>
			/// Maximum allowed ratio of average front wheel rotation speed and rear wheel rotation speeds.
			/// </summary>
			property float CentreBias;
			/// <summary>
			/// Maximum allowed ratio of front-left and front-right wheel rotation speeds.
			/// </summary>
			property float FrontBias;
			/// <summary>
			/// Maximum allowed ratio of rear-left and rear-right wheel rotation speeds.
			/// </summary>
			property float RearBias;
			/// <summary>
			/// Type of differential. Range: (VehicleDifferentialType.LS4WheelDrive, VehicleDifferentialType.LSFrontWheelDrive).
			/// </summary>
			property VehicleDifferentialType Type;
	};
};