using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class ControllerSample
	{
		public static PhysX.Controller CapsuleController(Scene scene)
		{
			var manager = scene.CreateControllerManager();

			var capsuleControllerDesc = new CapsuleControllerDescription(4, 3)
			{
				Callback = new ControllerHitReport()
			};

			var capsuleController = manager.CreateController<CapsuleController>(capsuleControllerDesc);
			capsuleController.Position = new Vector3(-10, 1.5f + 2, 0);
			capsuleController.Actor.Name = "BoxController";
			capsuleController.SetCollisionEnabled(true);

			return capsuleController;
		}
	}
}