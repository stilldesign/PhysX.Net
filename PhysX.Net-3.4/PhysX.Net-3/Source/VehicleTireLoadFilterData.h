#pragma once


namespace PhysX
{
	/// <summary>
	/// Tire load can be strongly dependent on the timestep so it is a good idea to filter it to give
	/// less jerky handling behaviour. The filtered tyre load is used as an input to the tyre model.
	/// </summary>
	/// <remarks>
	/// Two points on graph with normalised tyre load on x-axis and filtered normalised tyre
	/// load on y-axis. Loads less than mMinNormalisedLoad have filtered normalised
	/// load = zero. Loads greater than mMaxNormalisedLoad have filtered normalised
	/// load = mMaxFilteredNormalisedLoad. Loads in-between are linearly interpolated between 0
	/// and mMaxFilteredNormalisedLoad. The two graphs points that we specify are (MinNormalisedLoad,0) and
	/// (MaxNormalisedLoad, MaxFilteredNormalisedLoad). 
	/// </remarks>
	public ref class VehicleTireLoadFilterData
	{
		internal:
			static VehicleTireLoadFilterData^ ToManaged(PxVehicleTireLoadFilterData data);
			static PxVehicleTireLoadFilterData ToUnmanaged(VehicleTireLoadFilterData^ data);

		public:
			property float Denominator
			{
				float get();
			}

			/// <summary>
			/// Graph point (MinNormalisedLoad, 0).
			/// </summary>
			property float MinNormalisedLoad;

			/// <summary>
			/// Graph point (MaxNormalisedLoad, MaxFilteredNormalisedLoad).
			/// </summary>
			property float MaxNormalisedLoad;

			/// <summary>
			/// Graph point (MaxNormalisedLoad, MaxFilteredNormalisedLoad).
			/// </summary>
			property float MaxFilteredNormalisedLoad;
	};
};