using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class ObservableTest : Test
	{
		[TestMethod]
		public void GetObservableType()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var actor = core.Physics.CreateRigidDynamic();

				Assert.AreEqual(ObservableType.Actor, actor.GetObservableType());
			}
		}

		[TestMethod]
		public void GetNumberOfObservers_InitiallyZero()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var actor = core.Physics.CreateRigidDynamic();

				Assert.AreEqual(0, actor.GetNumberOfObservers());
			}
		}

		[TestMethod]
		public void GetObservers_InitiallyZero()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var actor = core.Physics.CreateRigidDynamic();

				Assert.IsNotNull(actor.GetObservers());
				Assert.AreEqual(0, actor.GetObservers().Length);
			}
		}
	}
}