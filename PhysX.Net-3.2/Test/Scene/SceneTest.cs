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
			using (var foundation = new Foundation())
			{
				using (var physics = new Physics(foundation))
				{
					var sceneDesc = new SceneDesc();

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
		}

		[TestMethod]
		public void SetGravity()
		{
			using (var core = CreatePhysicsAndScene())
			{
				core.Scene.Gravity = new Vector3(0, -9.81f, 0);

				Assert.AreEqual(new Vector3(0, -9.81f, 0), core.Scene.Gravity);
			}
		}

		[TestMethod]
		public void RaycastAny()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// On the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 0, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 0, 40);

				var hit = core.Scene.RaycastAny(new Vector3(0, 0, 0), new Vector3(0, 0, 1), 10000);

				// Calling RaycastAny returns flags of Material | FaceNormal | Distance | Normal | Impact | Shape, so validate those variables
				Assert.IsNotNull(hit);
				//Assert.AreEqual(17.5f, hit.);
				//Assert.AreEqual(new Vector3(0, 0, -1), hit.WorldNormal);
				//Assert.AreEqual(ray.Origin + ray.Direction * 17.5f, hit.WorldImpact);
				Assert.IsNotNull(hit.Shape);
				Assert.AreEqual(box1.Shapes.First(), hit.Shape);
				Assert.AreEqual(box1, hit.Shape.Actor);
			}
		}

		[TestMethod]
		public void RaycastSingle()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				Vector3 origin = new Vector3(0, 2, 0);
				Vector3 direction = new Vector3(0, 0, 1);

				var hit = core.Scene.RaycastSingle(origin, direction, 10000, SceneQueryFlags.Distance | SceneQueryFlags.BlockingHit | SceneQueryFlags.Normal);

				Assert.IsNotNull(hit);
				Assert.AreEqual(17.5f, hit.Distance);
				Assert.AreEqual(new Vector3(0, 0, -1), hit.Normal);
				Assert.AreEqual(new Vector3(0, 2, 17.5f), hit.Impact);
				Assert.IsNotNull(hit.Shape);
				Assert.AreEqual(box1.Shapes.First(), hit.Shape);
				Assert.AreEqual(box1, hit.Shape.Actor);
			}
		}

		[TestMethod]
		public void RaycastMultiple()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				Vector3 origin = new Vector3(0, 2, 0);
				Vector3 direction = new Vector3(0, 0, 1);

				var hit = core.Scene.RaycastMultiple
				(
					origin: origin, 
					direction: direction,
					distance: 10000,
					outputFlags: SceneQueryFlags.Distance | SceneQueryFlags.BlockingHit | SceneQueryFlags.Normal,
					hitBufferSize: 2
				);

				Assert.IsNotNull(hit);
				Assert.AreEqual(2, hit.Length);

				RaycastHit a = hit[0];

				Assert.AreEqual(17.5f, a.Distance);
				Assert.AreEqual(new Vector3(0, 0, -1), a.Normal);
				Assert.AreEqual(new Vector3(0, 2, 17.5f), a.Impact);
				Assert.IsNotNull(a.Shape);
				Assert.AreEqual(box1.Shapes.First(), a.Shape);
				Assert.AreEqual(box1, a.Shape.Actor);

				RaycastHit b = hit[1];

				Assert.AreEqual(37.5f, b.Distance);
				Assert.AreEqual(new Vector3(0, 0, -1), b.Normal);
				Assert.AreEqual(new Vector3(0, 2, 37.5f), b.Impact);
				Assert.IsNotNull(b.Shape);
				Assert.AreEqual(box2.Shapes.First(), b.Shape);
				Assert.AreEqual(box2, b.Shape.Actor);
			}
		}

		[TestMethod]
		public void OverlapAny()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				box1.Name = "Box1";
				box2.Name = "Box2";

				BoxGeometry overlappingBox = new BoxGeometry(100, 100, 100);

				var overlap = core.Scene.OverlapAny(overlappingBox, Matrix.Identity);

				Assert.IsNotNull(overlap);
				Assert.AreEqual(box2, overlap.Actor);
			}
		}

		[TestMethod]
		public void OverlapMultiple()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				box1.Name = "Box1";
				box2.Name = "Box2";

				BoxGeometry overlappingBox = new BoxGeometry(100, 100, 100);

				var overlap = core.Scene.OverlapMultiple(overlappingBox, Matrix.Identity);

				Assert.IsNotNull(overlap);
				Assert.AreEqual(2, overlap.Length);
				Assert.AreEqual(box2, overlap[0].Actor);
				Assert.AreEqual(box1, overlap[1].Actor);
			}
		}

		[TestMethod]
		public void SweepAny()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				box1.Name = "Box1";
				box2.Name = "Box2";

				// Use a box of 10x10x10 to sweep with
				BoxGeometry sweepBox = new BoxGeometry(10, 10, 10);

				// Sweep the box forwards 25 units to hit box1
				var sweep = core.Scene.SweepAny
				(
					sweepBox, 
					Matrix.Translation(0, 2, 0),
					new Vector3(0, 0, 1),
					25,
					SceneQueryFlags.All
				);

				Assert.IsNotNull(sweep);
				Assert.AreEqual(box1, sweep.Shape.Actor);
			}
		}

		[TestMethod]
		[Ignore]
		// This test throws an 'attempted to write to protected memory' exception, which causes
		// the using/dispose method to be NOT called, and everything fails from there...
		public void SweepMultiple()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				box1.Name = "Box1";
				box2.Name = "Box2";

				// Use a box of 10x10x10 to sweep with
				BoxGeometry sweepBox = new BoxGeometry(10, 10, 10);

				// Sweep the box forwards 25 units to hit box1
				var sweep = core.Scene.SweepMultiple
				(
					sweepBox,
					Matrix.Translation(0, 2, 0),
					null,
					new Vector3(0, 0, 1),
					25,
					SceneQueryFlags.All,
					2,
					null
				);

				Assert.IsNotNull(sweep);
				Assert.AreEqual(1, sweep.Count());

				var hit = sweep.ElementAt(0);
				Assert.IsNotNull(hit);
				Assert.IsNotNull(hit.Shape);
				Assert.AreEqual(box1, hit.Shape.Actor);
			}
		}

		[TestMethod]
		public void GetSimulationStatisticValues()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				CreateBoxActor(physics.Scene, 2, 3, 4);

				var stats = physics.Scene.GetSimulationStatistics();

				Assert.AreEqual(1, stats.NumberOfShapes[GeometryType.Box]);
				Assert.AreEqual(1, stats.NumberOfDynamicBodies);
			}
		}
	}
}