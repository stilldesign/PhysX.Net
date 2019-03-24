#pragma once

namespace PhysX
{
	public value class SolverIterationCounts
	{
		public:
			SolverIterationCounts(int minimumPositionIterations, int minimumVelocityIterations)
			{
				MinimumPositionIterations = minimumPositionIterations;
				MinimumVelocityIterations = minimumVelocityIterations;
			}

			property int MinimumPositionIterations;
			property int MinimumVelocityIterations;
	};
};