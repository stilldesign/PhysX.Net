using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.BroadPhase
{
	[TestClass]
	public class BroadPhaseTests : Test
	{
		[TestMethod]
		public void FromSceneDescToScene()
		{
			if (Physics.Instantiated)
				Assert.Fail("Physics is still created");

			using (var foundation = new Foundation())
			{
				var physics = new Physics(foundation, checkRuntimeFiles: true);

				var bpc = new TestBroadPhaseCallback();

				var sceneDesc = new SceneDesc
				{
					BroadPhaseCallback = bpc
				};

				var scene = physics.CreateScene(sceneDesc);

				Assert.AreEqual(bpc, scene.BroadPhaseCallback);
			}
		}

		//

		public class TestBroadPhaseCallback : BroadPhaseCallback
		{
			public override void OnObjectOutOfBounds(PhysX.Aggregate aggregate)
			{
				
			}

			public override void OnObjectOutOfBounds(Shape shape, PhysX.Actor actor)
			{
				
			}
		}
	}
}
