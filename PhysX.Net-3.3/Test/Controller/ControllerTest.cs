using System;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Controller
{
	[TestClass]
	public class ControllerTest : Test
	{
		[TestMethod]
		public void ControllerStateIsValid()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var controllerManager = core.Scene.CreateControllerManager();

				var material = core.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var desc = new CapsuleControllerDesc()
				{
					Height = 12,
					Radius = 7,
					Material = material,
					Position = new Vector3(0, 25, 0)
				};

				// Create a capsule controller
				var capsuleController = controllerManager.CreateController<CapsuleController>(desc);

				// A box for it to fall on to
				var box = CreateBoxActor(core.Scene, new Vector3(10, 1, 10), new Vector3(0, 0.5f, 0));

				// Make it fall
				for (int i = 0; i < 200; i++)
				{
					capsuleController.Move(new Vector3(0, -0.3f, 0), TimeSpan.FromMilliseconds(0.1));

					core.Scene.Simulate(0.1f);
					core.Scene.FetchResults(block: true);
				}

				//

				var controllerState = capsuleController.GetState();

				Assert.IsNotNull(controllerState);
				Assert.AreEqual(box.Shapes.First(), controllerState.TouchedShape);
				Assert.AreEqual(box, controllerState.TouchedActor);
				Assert.AreEqual(ControllerCollisionFlag.Down, controllerState.CollisionFlags);
			}
		}
	}
}