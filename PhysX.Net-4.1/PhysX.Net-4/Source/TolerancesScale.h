#pragma once

namespace PhysX
{
	/// <summary>
	/// Class to define the scale at which simulation runs. Most simulation tolerances are calculated in terms of the values here
	/// </summary>
	/// <remarks>
	/// If you change the simulation scale, you will probablly also wish to change the scene's default value of gravity, and stable simulation will probably require changes to the scene's bounceThreshold also.
	/// </remarks>
	public value class TolerancesScale
	{
		internal:
			static PxTolerancesScale ToUnmanaged(TolerancesScale scale);
			static TolerancesScale ToManaged(PxTolerancesScale scale);

		public:
			/// <summary>
			/// The approximate size of objects in the simulation.
			/// For simulating roughly human-sized in metric units, 1 is a good choice. If simulation is done in centimetres, use 100 instead. This is used to estimate certain length-related tolerances.
			/// </summary>
			property float Length;
			/// <summary>
			/// The typical magnitude of velocities of objects in simulation. This is used to estimate whether a contact should be treated as bouncing or resting based on its impact velocity, and a kinetic energy threshold below which the simulation may put objects to sleep.
			/// For normal physical environments, a good choice is the approximate speed of an object falling under gravity for one second.
			/// </summary>
			property float Speed;

			//

			/// <summary>
			/// Gets a new instance of TolerancesScale with its fields set to default values.
			/// </summary>
			property TolerancesScale Default
			{
				static TolerancesScale get();
			}
	};
};