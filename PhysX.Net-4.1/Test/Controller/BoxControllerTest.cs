using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class BoxControllerTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeBoxController()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var controllerManager = core.Scene.CreateControllerManager();

				var material = core.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

				var desc = new CapsuleControllerDesc()
				{
					Height = 12,
					Radius = 7,
					Material = material
				};

				Assert.IsTrue(desc.IsValid());

				CapsuleController capsuleController;
				using (capsuleController = controllerManager.CreateController<CapsuleController>(desc))
				{
					Assert.IsNotNull(capsuleController);
					Assert.IsFalse(capsuleController.Disposed);
				}

				Assert.IsTrue(capsuleController.Disposed);
			}
		}
	}
}