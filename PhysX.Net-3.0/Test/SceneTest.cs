using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class SceneTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeSceneInstance()
		{
			var sceneDesc = new SceneDesc();
			sceneDesc.IsValid();

			using (var physics = new Physics(new ErrorOutput()))
			{
				Scene scene;
				using (scene = physics.CreateScene(sceneDesc))
				{
					GC.Collect();

					Assert.IsFalse(scene.Disposed);
				}

				Assert.IsFalse(physics.Disposed);
				Assert.IsTrue(scene.Disposed);
			}
		}

		[TestMethod]
		public void SetGravity()
		{
			using (CreatePhysicsAndScene())
			{
				this.Scene.Gravity = new Vector3(0, -9.81f, 0);

				Assert.AreEqual(new Vector3(0, -9.81f, 0), this.Scene.Gravity);
			}
		}

		[TestMethod]
		public void RaycastAny()
		{
			using (CreatePhysicsAndScene())
			{
				// On the ground, 20 units ahead
				var box1 = CreateBoxActor(0, 0, 20);
				var box2 = CreateBoxActor(0, 0, 40);

				var hit = this.Scene.RaycastAny(new Vector3(0, 0, 0), new Vector3(0, 0, 1), 10000);

				// Calling RaycastAny returns flags of Material | FaceNormal | Distance | Normal | Impact | Shape, so validate those variables
				Assert.IsNotNull(hit);
				//Assert.AreEqual(17.5f, hit.);
				//Assert.AreEqual(new Vector3(0, 0, -1), hit.WorldNormal);
				//Assert.AreEqual(ray.Origin + ray.Direction * 17.5f, hit.WorldImpact);
				Assert.AreEqual(box1, hit.Actor);
				Assert.AreEqual(box1.Shapes.First(), hit.Shape);
			}
		}

		[TestMethod]
		public void RaycastSingle()
		{
			using (CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(0, 2, 20);
				var box2 = CreateBoxActor(0, 2, 40);

				Vector3 origin = new Vector3(0, 2, 0);
				Vector3 direction = new Vector3(0, 0, 1);

				var hit = this.Scene.RaycastSingle(origin, direction, 10000, SceneQueryFlags.Distance | SceneQueryFlags.BlockingHit | SceneQueryFlags.Normal);

				Assert.IsNotNull(hit);
				Assert.AreEqual(17.5f, hit.Distance);
				Assert.AreEqual(new Vector3(0, 0, -1), hit.Normal);
				Assert.AreEqual(new Vector3(0, 2, 17.5f), hit.Impact);
				Assert.AreEqual(box1, hit.Actor);
				Assert.AreEqual(box1.Shapes.First(), hit.Shape);
			}
		}
	}
}