#pragma once


namespace PhysX
{
	public ref class VehicleChassisData
	{
		internal:
			static PxVehicleChassisData ToUnmanaged(VehicleChassisData^ data);
			static VehicleChassisData^ ToManaged(PxVehicleChassisData data);

		public:
			/// <summary>
			/// Gets or sets the moment of inertia of vehicle rigid body actor.
			/// </summary>
			property Vector3 MomentOfInertia;

			/// <summary>
			/// Gets or sets the mass of vehicle rigid body actor.
			/// </summary>
			property float Mass;

			/// <summary>
			/// Gets or sets the center of mass offset of vehicle rigid body actor.
			/// </summary>
			property Vector3 CenterOfMassOffset;
	};
};