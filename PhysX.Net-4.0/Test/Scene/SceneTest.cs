using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;
using PhysX.Test.Util;

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
		public void Raycast()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				Vector3 origin = new Vector3(0, 2, 0);
				Vector3 direction = new Vector3(0, 0, 1);

				RaycastHit[] hits = null;

				bool hadHit = core.Scene.Raycast
				(
					origin,
					direction,
					distance: 10000,
					maximumHits: 2,
					hitCall: h =>
					{
						hits = h;

						// Return hit again (PxAgain)
						return true;
					},
					hitFlag: HitFlag.Normal | HitFlag.Position
				);

				Assert.IsNotNull(hits);

				var hit = hits[0];

				Assert.IsNotNull(hit);
				Assert.AreEqual(17.5f, hit.Distance);
				Assert.AreEqual(new Vector3(0, 0, -1), hit.Normal);
				Assert.AreEqual(new Vector3(0, 2, 17.5f), hit.Position);
				Assert.IsNotNull(hit.Shape);
				Assert.AreEqual(box1.Shapes.First(), hit.Shape);
				Assert.AreEqual(box1, hit.Shape.Actor);
			}
		}

		[TestMethod]
		public void Overlap()
		{
			using (var core = CreatePhysicsAndScene())
			{
				// Just up from the ground, 20 units ahead
				var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
				var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

				box1.Name = "Box1";
				box2.Name = "Box2";

				BoxGeometry overlappingBox = new BoxGeometry(100, 100, 100);

				OverlapHit[] hits = null;

				bool result = core.Scene.Overlap
				(
					geometry: overlappingBox,
					pose: Matrix4x4.Identity,
					maximumOverlaps: 2,
					hitCall: hit =>
					{
						hits = hit;

						return true;
					}
				);

				Assert.IsNotNull(hits);
				Assert.AreEqual(2, hits.Length);

				var hitActors = hits.Select(h => h.Actor).ToArray();
				CollectionAssert.Contains(hitActors, box1);
				CollectionAssert.Contains(hitActors, box2);
			}
		}

		//[TestMethod]
		//public void SweepAny()
		//{
		//	using (var core = CreatePhysicsAndScene())
		//	{
		//		// Just up from the ground, 20 units ahead
		//		var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
		//		var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

		//		box1.Name = "Box1";
		//		box2.Name = "Box2";

		//		// Use a box of 10x10x10 to sweep with
		//		BoxGeometry sweepBox = new BoxGeometry(10, 10, 10);

		//		// Sweep the box forwards 25 units to hit box1
		//		var sweep = core.Scene.SweepAny
		//		(
		//			sweepBox, 
		//			Matrix4x4.CreateTranslation(0, 2, 0),
		//			new Vector3(0, 0, 1),
		//			25,
		//			SceneQueryFlags.All
		//		);

		//		Assert.IsNotNull(sweep);
		//		Assert.AreEqual(box1, sweep.Shape.Actor);
		//	}
		//}

		//[TestMethod]
		//[Ignore]
		//// This test throws an 'attempted to write to protected memory' exception, which causes
		//// the using/dispose method to be NOT called, and everything fails from there...
		//public void SweepMultiple()
		//{
		//	using (var core = CreatePhysicsAndScene())
		//	{
		//		// Just up from the ground, 20 units ahead
		//		var box1 = CreateBoxActor(core.Scene, 0, 2, 20);
		//		var box2 = CreateBoxActor(core.Scene, 0, 2, 40);

		//		box1.Name = "Box1";
		//		box2.Name = "Box2";

		//		// Use a box of 10x10x10 to sweep with
		//		BoxGeometry sweepBox = new BoxGeometry(10, 10, 10);

		//		// Sweep the box forwards 25 units to hit box1
		//		var sweep = core.Scene.SweepMultiple
		//		(
		//			sweepBox,
		//			Matrix4x4.CreateTranslation(0, 2, 0),
		//			null,
		//			new Vector3(0, 0, 1),
		//			25,
		//			SceneQueryFlags.All,
		//			2,
		//			null
		//		);

		//		Assert.IsNotNull(sweep);
		//		Assert.AreEqual(1, sweep.Count());

		//		var hit = sweep.ElementAt(0);
		//		Assert.IsNotNull(hit);
		//		Assert.IsNotNull(hit.Shape);
		//		Assert.AreEqual(box1, hit.Shape.Actor);
		//	}
		//}

		[TestMethod]
		public void GetSimulationStatisticValues()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				CreateBoxActor(physics.Scene, 2, 3, 4);

				var stats = physics.Scene.GetSimulationStatistics();

				Assert.AreEqual(1, stats.Shapes[GeometryType.Box]);
				Assert.AreEqual(1, stats.DynamicBodies);
			}
		}

		[TestMethod]
		public void GetSetSceneLimits()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				physics.Scene.SceneLimits = new SceneLimits()
				{
					MaxActors = 1,
					MaxBodies = 2,
					MaxConstraints = 3,
					MaxDynamicShapes = 4,
					MaxRegions = 5,
					MaxStaticShapes = 6,
					MaxAggregates = 7,
					MaxBroadPhaseOverlaps = 8
				};

				var limits = physics.Scene.SceneLimits;

				Assert.AreEqual(1, limits.MaxActors);
				Assert.AreEqual(2, limits.MaxBodies);
				Assert.AreEqual(3, limits.MaxConstraints);
				Assert.AreEqual(4, limits.MaxDynamicShapes);
				Assert.AreEqual(5, limits.MaxRegions);
				Assert.AreEqual(6, limits.MaxStaticShapes);
				Assert.AreEqual(7, limits.MaxAggregates);
				Assert.AreEqual(8, limits.MaxBroadPhaseOverlaps);
			}
		}

		[TestMethod]
		public void SceneDescFlagsAreMaintained()
		{
			using (var physics = new Physics(new Foundation()))
			{
				var sceneDesc = new SceneDesc
				{
					Flags = SceneFlag.EnableGpuDynamics | SceneFlag.EnableStabilization
				};

				var scene = physics.CreateScene(sceneDesc);

				Assert.IsTrue(scene.Flags.HasFlag(SceneFlag.EnableGpuDynamics));
				Assert.IsTrue(scene.Flags.HasFlag(SceneFlag.EnableStabilization));
			}
		}

		[TestMethod]
		public void GetActors_RigidDynamic()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var dynamicActor = CreateBoxActor(physics.Scene, 3, 3, 3);

				//

				var actors = physics.Scene.GetActors(ActorTypeFlag.RigidDynamic);

				Assert.AreEqual(1, actors.Count);
				Assert.AreEqual(dynamicActor, actors[0]);
			}
		}
		[TestMethod]
		public void GetActors_RigidStatic()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Scene.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);
				var staticActor = physics.Scene.Physics.CreateRigidStatic();
				var shape = staticActor.CreateShape(new BoxGeometry(5, 5, 5), material);
				physics.Scene.AddActor(staticActor);

				//

				var actors = physics.Scene.GetActors(ActorTypeFlag.RigidStatic);

				Assert.AreEqual(1, actors.Count);
				Assert.AreEqual(staticActor, actors[0]);
			}
		}

		[TestMethod]
		public void CreateSceneWithTemporalGaussSeidelSolver()
		{
			using (var physics = CreatePhysics())
			{
				var sceneDesc = new SceneDesc
				{
					SolverType = SolverType.TGS
				};

				using (var scene = physics.CreateScene(sceneDesc))
				{
					
				}
			}
		}
	}
}