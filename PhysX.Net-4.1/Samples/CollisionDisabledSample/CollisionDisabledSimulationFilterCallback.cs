using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace PhysX.Samples.CollisionDisabledSample
{
	public class CollisionDisabledSimulationFilterCallback : PhysX.SimulationFilterCallback
	{
		public List<Tuple<RigidActor, RigidActor>> DisableCollisionBetweenActors { get; } = new List<Tuple<RigidActor, RigidActor>>();

		public override PairFoundResult PairFound(int pairId,
			int attributes0, FilterData filterData0, Actor a0, Shape s0,
			int attributes1, FilterData filterData1, Actor a1, Shape s1,
			PairFlag pairFlags)
		{
			// Check if the two colliding actors are ones we want to disable collision on
			// a0 and a1 can be in either order, so we need to check [a0, a1] and [a1, a0]
			bool disableCollision = this.DisableCollisionBetweenActors.Any(d => (d.Item1 == a0 || d.Item2 == a0) && (d.Item1 == a1 || d.Item2 == a1));

			return new PairFoundResult
			{
				FilterFlags = disableCollision ? FilterFlag.Suppress : FilterFlag.Default,
				PairFlags = PairFlag.ContactDefault
			};
		}

		public override void PairLost(int pairId, int attributes0, FilterData filterData0, int attributes1, FilterData filterData1, bool objectRemoved)
		{
		}

		public override StatusChangeResult? StatusChange(int pairId, PairFlag pairFlags, FilterFlag filterFlags)
		{
			return null;
		}
	}
}
