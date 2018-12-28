#pragma once

namespace PhysX
{
	ref class RigidDynamic;

	/// <summary>
	/// Structure containing data that is computed for a wheel during concurrent calls to PxVehicleUpdates but which
	/// cannot be safely concurrently applied.
	/// </summary>
	public ref class VehicleWheelConcurrentUpdateData
	{
	//internal:
		//static PxVehicleWheelConcurrentUpdateData ToUnmanaged(VehicleWheelConcurrentUpdateData^ managed);

		// For some reason this data is private in the unmanaged class...
	public:
		property Matrix LocalPose;
		property RigidDynamic^ HitActor;
		property Vector3 HitActorForce;
		property Vector3 HitActorForcePosition;
	};
}