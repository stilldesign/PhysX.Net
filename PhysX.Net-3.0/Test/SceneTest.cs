using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;

namespace PhysX.Test
{
	[TestClass]
	public class SceneTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeSceneInstance()
		{
			var sceneDesc = new SceneDesc();

			var physics = new Physics();

			Scene scene;
			try
			{
				scene = physics.CreateScene(sceneDesc);
			}
			catch(SceneCreationException)
			{
				throw;
			}

			GC.Collect();

			Assert.IsFalse(scene.Disposed);

			scene.Dispose();

			Assert.IsTrue(scene.Disposed);
		}
	}
}