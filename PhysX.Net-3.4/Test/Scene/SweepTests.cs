using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class SweepTests : Test
	{
		[TestMethod]
		public void Box_Box_Sweep()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// Create a 10x10x10 box and place it to the right and on the ground
				var box = CreateBoxActor(physics.Scene, 5, 5, 5);
				box.GlobalPose = Matrix4x4.CreateTranslation(20, 5, 0);

				var sweepGeom = new BoxGeometry(2, 2, 2);

				//

				var hitActors = new List<RigidActor>();

				// Sweep the small box to the right 50units, it should hit our bigger box
				physics.Scene.Sweep(sweepGeom, Matrix4x4.CreateTranslation(0, 2, 0), new Vector3(1, 0, 0), 50, 10, (hits) =>
				{
					// Record all the hits to make sure we only end up with one
					hitActors.AddRange(hits.Select(h => h.Actor));

					return true;
				});

				Assert.AreEqual(1, hitActors.Count);
				Assert.AreEqual(box, hitActors[0]);
			}
		}
	}
}
