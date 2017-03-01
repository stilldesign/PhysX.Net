using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Controller
{
	[TestClass]
	public class ObstacleTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeObstacleContext()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var controllerManager = physics.Scene.CreateControllerManager();

				var obstacleContext = controllerManager.CreateObstacleContext();

				Assert.IsFalse(obstacleContext.Disposed);

				obstacleContext.Dispose();

				Assert.IsTrue(obstacleContext.Disposed);
			}
		}
	}
}