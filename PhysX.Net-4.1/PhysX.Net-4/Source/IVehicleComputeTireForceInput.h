#pragma once

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public interface class IVehicleComputeTireForceInput
	{
		/// <summary>
		/// The shader data for the tire being processed. The shader data describes the tire data in the format required by the tire model that is implemented by the shader function.  /// 
		/// </summary>
		property array<Byte>^ ShaderData
		{
			array<Byte>^ get();
		}

		/// <summary>
		/// The value of friction for the contact between the tire and the ground.
		/// </summary>
		property float TireFriction
		{
			float get();
		}

		/// <summary>
		/// the value of longitudinal slip experienced by the tire.
		/// </summary>
		property float LongitudinalSlip
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float LaterialSlip
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float Camber
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float WheelOmega
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float WheelRadius
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float ReciprocalWheelRadius
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float RestTireLoad
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float NormalisedTireLoad
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float TireLoad
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float Gravity
		{
			float get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float ReciprocalGravity
		{
			float get();
		}
	};
}