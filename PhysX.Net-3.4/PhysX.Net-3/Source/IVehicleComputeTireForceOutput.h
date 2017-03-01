#pragma once

namespace PhysX
{
	public interface class IVehicleComputeTireForceOutput
	{
		property float WheelTorque;
		property float TireLongitudinalForceMagnitude;
		property float TireLaterialForceMagnitude;
		property float TireAlignMoment;
	};
};