using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Threading;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class ContactModifyCallbackTest : Test
	{
		[Ignore] // Not finished yet
		[TestMethod]
		public void GetContactData()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// A box that will fall
				var box = CreateBoxActor(physics.Scene, new Vector3(5, 5, 5), new Vector3(0, 10, 0));

				// The ground
				var ground = CreateBoxActor(physics.Scene, new Vector3(100, 1, 100), new Vector3(0, 0, 0));
				ground.RigidBodyFlags = RigidBodyFlag.Kinematic; // Grounds don't move silly :P

				// Tell PhysX that the box and ground should raise collision callbacks
				DefaultSimulationFilterShader.SetGroup(box, 1);
				DefaultSimulationFilterShader.SetGroup(ground, 1);

				bool didTheBoxHitTheGround = false;

				physics.Scene.ContactModifyCallback = new TestContactModifyCallback(pairs =>
				{
					didTheBoxHitTheGround |= pairs.Any(p =>
						(p.ActorA == box && p.ActorB == ground) || 
						(p.ActorA == ground && p.ActorB == box));
				});

				// Wait for the cube to hit the ground and trigger the ContactModifyCallback. 3 seconds.
				for (int i = 0; i < 300; i++)
				{
					physics.Scene.Simulate(10);
				}

				Assert.IsTrue(didTheBoxHitTheGround);
			}
		}
	}

	public class TestContactModifyCallback : ContactModifyCallback
	{
		private Action<ContactModifyPair[]> _onContactModify;

		public TestContactModifyCallback(Action<ContactModifyPair[]> onContactModify)
		{
			_onContactModify = onContactModify;
		}

		public override void OnContactModify(ContactModifyPair[] pairs)
		{
			// Call the callback so our tests can assert the details
			_onContactModify(pairs);
		}
	}
}