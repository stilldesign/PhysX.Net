#pragma once

#include <PxVehicleUtils.h>

namespace PhysX
{
	/// <summary>
	/// Used to produce smooth analog driving control values from analog inputs.
	/// </summary>
	public ref class VehicleRawInputData : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxVehicleRawInputData* _inputData;

		internal:
			VehicleRawInputData(PxVehicleRawInputData* inputData);
		public:
			~VehicleRawInputData();
		protected:
			!VehicleRawInputData();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			array<bool>^ GetRawDigitalInputs();
			void SetRawDigitalInputs(array<bool>^ value);

			array<bool>^ GetRawAnalogInputs();
			void SetRawAnalogInputs(array<bool>^ value);

			property bool DigitalAccelerationKeyPressed
			{
				bool get();
				void set(bool value);
			}
			property bool DigitalBrakeKeyPressed
			{
				bool get();
				void set(bool value);
			}
			property bool DigitalHandbrakeKeyPressed
			{
				bool get();
				void set(bool value);
			}
			property bool DigitalSteerLeftKeyPressed
			{
				bool get();
				void set(bool value);
			}
			property bool DigitalSteerRightKeyPressed
			{
				bool get();
				void set(bool value);
			}
			property float AnalogAcceleration
			{
				float get();
				void set(float value);
			}
			property float AnalogBrake
			{
				float get();
				void set(float value);
			}
			property float AnalogHandbrake
			{
				float get();
				void set(float value);
			}
			property float AnalogSteer
			{
				float get();
				void set(float value);
			}
			property bool GearUpKeyPressed
			{
				bool get();
				void set(bool value);
			}
			property bool GearDownKeyPressed
			{
				bool get();
				void set(bool value);
			}

		internal:
			property PxVehicleRawInputData* UnmanagedPointer
			{
				PxVehicleRawInputData* get();
			}
	};
};