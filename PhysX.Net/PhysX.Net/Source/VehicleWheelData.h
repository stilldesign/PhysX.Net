#pragma once


namespace PhysX
{
	/// <summary>
	/// Used to produce smooth analog driving control values from analog inputs.
	/// </summary>
	public ref class VehicleWheelData
	{
		private:
			float _reciprocalRadius, _recipMomentOfInertia;

		internal:
			static VehicleWheelData^ ToManaged(PxVehicleWheelData wheelData);
			static PxVehicleWheelData ToUnmanaged(VehicleWheelData^ wheelData);

		public:
			/// <summary>
			/// Reciprocal of radius of unit that includes metal wheel plus rubber tyre. Not necessary to set this value. Range: (0,inf).
			/// </summary>
			property float ReciprocalRadius
			{
				float get();
			}

			/// <summary>
			/// Reciprocal of moment of inertia of unit that includes wheel plus tyre about single allowed axis of rotation. Not necessary to set this value. Range: (0,inf).
			/// </summary>
			property float RecipMomentOfInertia
			{
				float get();
			}
			
			/// <summary>
			/// Radius of unit that includes metal wheel plus rubber tyre, specified in m. Range: (0,inf).
			/// </summary>
			property float Radius;
			
			/// <summary>
			/// Maximum width of unit that includes wheel plus tyre, specified in m. Range: (0,inf).
			/// </summary>
			property float Width;
			
			/// <summary>
			/// Mass of unit that includes wheel plus tyre, specified in kg. Range: (0,inf).
			/// </summary>
			property float Mass;
			
			/// <summary>
			/// Moment of inertia of unit that includes wheel plus tyre about single allowed axis of rotation, specified in kg m^2. Range: (0,inf).
			/// </summary>
			property float MomentOfInertia;
			
			/// <summary>
			/// Damping rate applied to wheel.
			/// </summary>
			property float DampingRate;
			
			/// <summary>
			/// Max brake torque that can be applied to wheel, specified in Nm. Range: (0,inf).
			/// </summary>
			property float MaxBrakeTorque;
			
			/// <summary>
			/// Max handbrake torque that can be applied to wheel, specified in Nm Range: (0,inf).
			/// </summary>
			property float MaxHandBrakeTorque;
			
			/// <summary>
			/// Max steer angle that can be achieved by the wheel, specified in radians. Range: (0,inf).
			/// </summary>
			property float MaxSteer;
			
			/// <summary>
			/// Wheel toe angle, specified in radians. Range: (0,Pi/2).
			/// </summary>
			property float ToeAngle;
	};
};