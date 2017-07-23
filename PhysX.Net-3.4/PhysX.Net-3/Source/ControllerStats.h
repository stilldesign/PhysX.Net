#pragma once

namespace PhysX
{
	/// <summary>
	/// Describes a controller's internal statistics.
	/// </summary>
	public value class ControllerStats
	{
	internal:
		static ControllerStats ToManaged(PxControllerStats u);

	public:
		property int Iterations;
		property int FullUpdates;
		property int PartialUpdates;
		property int Tessellation;
	};
}