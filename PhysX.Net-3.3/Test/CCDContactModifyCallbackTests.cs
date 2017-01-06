using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class CCDContactModifyCallbackTests : Test
	{
		[TestMethod]
		public void TwoCCDActorsAreReportedForContactModification()
		{
			var errorLog = new ErrorLog();

			using (var foundation = new Foundation(errorLog))
			{
				var testCCDContactModifyCallback = new TestCCDContactModifyCallback();

				var physics = new Physics(foundation);

				var sceneDesc = new SceneDesc
				{
					Flags = SceneFlag.EnableCCD,
					Gravity = new Vector3(0),
					FilterShader = new TestFilterShader(),
					CCDContactModifyCallback = testCCDContactModifyCallback
				};

				int adi = AppDomain.CurrentDomain.Id;
				sceneDesc.SetSFS(MyClass.SFSGo);

				var scene = physics.CreateScene(sceneDesc);

				physics.RemoteDebugger.Connect("localhost");

				var box = CreateBoxActor(scene, size: new Vector3(0.2f, 0.2f, 0.2f), position: new Vector3(0, 20, 0));
				box.RigidBodyFlags |= RigidBodyFlag.EnableCCD;
				box.RigidBodyFlags |= RigidBodyFlag.EnableCCDFriction;
				box.SetMassAndUpdateInertia(10);

				var ground = CreateBoxActor(scene, new Vector3(20, 0.05f, 20), new Vector3(0));
				ground.RigidBodyFlags |= RigidBodyFlag.EnableCCD;
				ground.RigidBodyFlags |= RigidBodyFlag.EnableCCDFriction;
				ground.SetMassAndUpdateInertia(10);

				for (int i = 0; i < 1000; i++)
				{
					scene.Simulate(1f / 60f);
					scene.FetchResults(true);

					if (i == 100)
					{
						box.AddForce(new Vector3(0, -1000000, 0));
						ground.AddForce(new Vector3(0, 10000, 0));
					}
				}

				CollectionAssert.Contains(testCCDContactModifyCallback.ContactedActors, box);
				CollectionAssert.Contains(testCCDContactModifyCallback.ContactedActors, ground);
			}
		}

		

		public class TestCCDContactModifyCallback : PhysX.CCDContactModifyCallback
		{
			public List<RigidActor> ContactedActors { get; set; } = new List<RigidActor>();

			public override void OnCCDContactModify(ContactModifyPair[] pairs)
			{
				this.ContactedActors.AddRange(pairs.Select(p => p.ActorA));
				this.ContactedActors.AddRange(pairs.Select(p => p.ActorB));
			}
		}

		public class TestFilterShader : SimulationFilterShader
		{
			public FilterResult Filter(int attributes0, FilterData filterData0, int attributes1, FilterData filterData1)
			{
				return new FilterResult
				{
					PairFlags = PairFlag.SolveContact | PairFlag.DetectDiscreteContact | PairFlag.DetectCCDContact | PairFlag.ModifyContacts
				};
			}
		}
	}

	public static class MyClass
	{
		public static void SFSGo()
		{
			int k = 3;
			k /= 2;
		}
	}
}
