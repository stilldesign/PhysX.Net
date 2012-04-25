#pragma once

#include <PxVehicle.h>

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleAckermannGeometryData : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxVehicleAckermannGeometryData* _data;

			VehicleAckermannGeometryData(PxVehicleAckermannGeometryData* data);
		public:
			~VehicleAckermannGeometryData();
		protected:
			!VehicleAckermannGeometryData();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Accuracy of Ackermann steer calculation. Range: (0,1).
			/// </summary>
			property float Accuracy
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Distance between centre-point of the two front wheels, specified in m. Range: (0,inf).
			/// </summary>
			property float FrontWidth
			{
				float get();
			}

			/// <summary>
			/// Distance between centre of front axle and centre of rear axle, specified in m. Range: (0,inf).
			/// </summary>
			property float AxleSeparation
			{
				float get();
			}

		internal:
			property PxVehicleAckermannGeometryData* UnmanagedPointer
			{
				PxVehicleAckermannGeometryData* get();
			}
	};
};