#pragma once
#include <PxVehicle.h>

namespace PhysX
{
	public ref class VehicleTyreData
	{
		internal:
			static VehicleTyreData^ ToManaged(PxVehicleTyreData tyreData);
			static PxVehicleTyreData ToUnmanaged(VehicleTyreData^ tyreData);

		public:
			/// <summary>
			/// Tyre lateral stiffness is typically a graph of tyre load that has linear behaviour near zero
			/// load and flattens at large loads. mLatStiffX describes the minimum normalised load
			/// (load/restLoad) that gives a flat lateral stiffness response. Range: (0,inf).
			/// </summary>
			property float LateralStiffnessX;

			/// <summary>
			/// Tyre lateral stiffness is a graph of tyre load that has linear behaviour near zero
			/// load and flattens at large loads. mLatStiffY describes the maximum possible lateral
			/// stiffness divided by the rest tyre load, specified in "per radian" Range: (0,inf).
			/// </summary>
			property float LateralStiffnessY;

			/// <summary>
			/// Tyre Longitudinal stiffness of the tyre, specified in N per radian. Range: (0,inf).
			/// </summary>
			property float LongitudinalStiffness;

			/// <summary>
			/// Camber stiffness, specified in N per radian. Range: (0,inf).
			/// </summary>
			property float CamberStiffness;

			/// <summary>
			/// Graph of friction vs longitudinal slip with 3 points.
			/// </summary>
			property array<array<float>^>^ FrictionVsSlipGraph;

			/// <summary>
			/// Tyre type denoting slicks, wets, snow, winter, summer, all-terrain, mud etc. Range: (0,inf).
			/// </summary>
			property int Type;
	};
};