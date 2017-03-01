#pragma once

namespace PhysX
{
	ref class VehicleWheelConcurrentUpdateData;

	/// <summary>
	/// Structure containing data that is computed for a vehicle and its wheels during concurrent calls to PxVehicleUpdates but which cannot be safely concurrently applied.
	/// </summary>
	public ref class VehicleConcurrentUpdateData
	{
	public:
		/// <summary>
		/// Pointer to an PxVehicleWheelConcurrentUpdate buffer of length nbConcurrentWheelUpdates The concurrentWheelUpdates buffer
		/// must persist until the end of PxVehiclePostUpdates A NULL pointer is not permitted.
		/// </summary>
		property VehicleWheelConcurrentUpdateData^ ConcurrentWheelUpdates;
	};
}