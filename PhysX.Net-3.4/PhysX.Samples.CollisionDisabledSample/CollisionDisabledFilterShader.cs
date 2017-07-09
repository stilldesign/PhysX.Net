using System;

namespace PhysX.Samples.CollisionDisabledSample
{
	public class CollisionDisabledFilterShader : SimulationFilterShader
	{
		public override FilterResult Filter(int attributes0, FilterData filterData0, int attributes1, FilterData filterData1)
		{
			return new FilterResult
			{
				// Set FilterFlag to Callback to enable CollisionDisabledSimulationFilterCallback to be used
				FilterFlag = FilterFlag.Callback,
				PairFlags = PairFlag.ContactDefault
			};
		}
	}
}
