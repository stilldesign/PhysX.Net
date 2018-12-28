#pragma once

namespace PhysX
{
	public ref class VehicleTireData
	{
		internal:
			static VehicleTireData^ ToManaged(PxVehicleTireData tireData);
			static PxVehicleTireData ToUnmanaged(VehicleTireData^ tireData);

		public:
			/// <summary>
			/// Tire lateral stiffness is typically a graph of tire load that has linear behaviour near zero
			/// load and flattens at large loads. mLatStiffX describes the minimum normalised load
			/// (load/restLoad) that gives a flat lateral stiffness response. Range: (0,inf).
			/// </summary>
			property float LateralStiffnessX;

			/// <summary>
			/// Tire lateral stiffness is a graph of tire load that has linear behaviour near zero
			/// load and flattens at large loads. mLatStiffY describes the maximum possible lateral
			/// stiffness divided by the rest tire load, specified in "per radian" Range: (0,inf).
			/// </summary>
			property float LateralStiffnessY;

			/// <summary>
			/// Tire Longitudinal stiffness of the tire, specified in N per radian. Range: (0,inf).
			/// </summary>
			property float LongitudinalStiffnessPerUnitGravity;

			/// <summary>
			/// Camber stiffness, specified in N per radian. Range: (0,inf).
			/// </summary>
			property float CamberStiffnessPerUnitGravity;

			/// <summary>
			/// Graph of friction vs longitudinal slip with 3 points.
			/// </summary>
			//property array<array<float>^>^ FrictionVsSlipGraph;

			/// <summary>
			/// Tire type denoting slicks, wets, snow, winter, summer, all-terrain, mud etc. Range: (0,inf).
			/// </summary>
			property int Type;
	};
};