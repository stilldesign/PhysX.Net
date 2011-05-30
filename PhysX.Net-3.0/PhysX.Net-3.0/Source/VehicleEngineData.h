#pragma once

#include "VehicleEnum.h"
#include <PxVehicle.h>

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class VehicleEngineData : IDisposable
	{
		public:
			static const int MaximumNumberOfEngineTorqueCurveEntries = PxVehicleEngineData::eMAX_NUM_ENGINE_TORQUE_CURVE_ENTRIES;

			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxVehicleEngineData* _engineData;

		private:
			VehicleEngineData(PxVehicleEngineData* engineData);
		public:
			~VehicleEngineData();
		protected:
			!VehicleEngineData();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Maximum torque available to apply to the engine, specified in Nm. Range: (0, inf).
			/// </summary>
			property float PeakTorque
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Maximum rotation speed of the engine, specified in radians per second. Range: (0, inf).
			/// </summary>
			property float MaxOmega
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Damping rate of engine when the clutch is engaged, specified in s^-1. Range: (0, inf).
			/// </summary>
			property float EngagedClutchDampingRate
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Damping rate of engine when the clutch is not engaged, specified in s^-1. Range: (0, inf).
			/// </summary>
			property float DisengagedClutchDampingRate
			{
				float get();
				void set(float value);
			}

		internal:
			property PxVehicleEngineData* UnmanagedPointer
			{
				PxVehicleEngineData* get();
			}
	};
};