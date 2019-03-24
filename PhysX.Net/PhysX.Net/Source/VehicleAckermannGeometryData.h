#pragma once


namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleAckermannGeometryData
	{
	internal:
		static VehicleAckermannGeometryData^ ToManaged(PxVehicleAckermannGeometryData data);
		static PxVehicleAckermannGeometryData ToUnmanaged(VehicleAckermannGeometryData^ data);

	public:
		/// <summary>
		/// Accuracy of Ackermann steer calculation. Range: (0,1).
		/// </summary>
		property float Accuracy;

		/// <summary>
		/// Distance between centre-point of the two front wheels, specified in m. Range: (0,inf).
		/// </summary>
		property float FrontWidth;

		/// <summary>
		/// Distance between center-point of the two rear wheels, specified in m. Range: (0,inf).
		/// </summary>
		property float RearWidth;

		/// <summary>
		/// Distance between centre of front axle and centre of rear axle, specified in m. Range: (0,inf).
		/// </summary>
		property float AxleSeparation;
	};
};