using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Actor
{
	[TestClass]
	public class ActorTest : Test
	{
		[TestMethod]
		public void ActorCollectionOfScene()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.3f, 0.1f);

				Assert.AreEqual(0, physics.Scene.Actors.Count());

				var rigidActor1 = physics.Scene.Physics.CreateRigidDynamic();

				Assert.AreEqual(1, physics.Scene.Actors.Count());

				var rigidActor2 = physics.Scene.Physics.CreateRigidDynamic();

				Assert.AreEqual(2, physics.Scene.Actors.Count());
			}
		}
	}
}