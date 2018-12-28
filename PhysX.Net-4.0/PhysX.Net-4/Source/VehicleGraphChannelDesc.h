#pragma once


namespace PhysX
{
	public ref class VehicleGraphChannelDesc
	{
		internal:
			static VehicleGraphChannelDesc^ FromUnmanaged(PxVehicleGraphChannelDesc desc);
			static PxVehicleGraphChannelDesc ToUnmanaged(VehicleGraphChannelDesc^ desc);

		public:
			/// <summary>
			/// Data values less than MinY will be clamped at MinY.
			/// </summary>
			property float MinY;

			/// <summary>
			/// Data values greater than MaxY will be clamped at MaxY.
			/// </summary>
			property float MaxY;

			/// <summary>
			/// Data values greater than MidY will be drawn with colour ColorHigh.
			/// </summary>
			property float MidY;

			/// <summary>
			/// Color used to render data values lower than MidY.
			/// </summary>
			property Vector3 ColorLow;

			/// <summary>
			/// Color used to render data values greater than mMidY.
			/// </summary>
			property Vector3 ColorHigh;

			/// <summary>
			/// String to describe data channel.
			/// </summary>
			property String^ Title;
	};
};