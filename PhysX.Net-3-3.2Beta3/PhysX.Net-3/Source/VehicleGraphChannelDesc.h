#pragma once

#include <PxVehicleUtils.h>

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
			/// Data values greater than MidY will be drawn with colour ColourHigh.
			/// </summary>
			property float MidY;

			/// <summary>
			/// Colour used to render data values lower than MidY.
			/// </summary>
			property Vector3 ColourLow;

			/// <summary>
			/// Colour used to render data values greater than mMidY.
			/// </summary>
			property Vector3 ColourHigh;

			/// <summary>
			/// String to describe data channel.
			/// </summary>
			property String^ Title;
	};
};