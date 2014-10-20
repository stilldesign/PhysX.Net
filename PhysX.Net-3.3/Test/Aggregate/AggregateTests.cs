using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Aggregate
{
	[TestClass]
	public class AggregateTests : Test
	{
		[TestMethod]
		public void CreateAndDispose()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var agg = physics.Physics.CreateAggregate(100, true);

				agg.Dispose();

				Assert.IsFalse(ObjectTable.Contains(agg));
			}
		}

		[TestMethod]
		public void GetActor()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var agg = physics.Physics.CreateAggregate(100, true);

				var actor = physics.Physics.CreateRigidDynamic();

				bool added = agg.AddActor(actor);

				Assert.IsTrue(added);
				Assert.AreEqual(actor, agg.GetActor(0));
			}
		}

		[TestMethod]
		public void GetActors()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var agg = physics.Physics.CreateAggregate(100, true);

				var actor1 = physics.Physics.CreateRigidDynamic();
				var actor2 = physics.Physics.CreateRigidDynamic();

				agg.AddActor(actor1);
				agg.AddActor(actor2);

				var actors = agg.GetActors();

				Assert.AreEqual(actor1, actors[0]);
				Assert.AreEqual(actor2, actors[1]);
			}
		}
	}
}