using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;
using PhysX.MathPrimitives;

namespace PhysX.Test
{
	[TestClass]
	public class ParticleTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeParticleSystemInstance()
		{
			using (var physics = new Physics())
			{
				var desc = new ParticleSystemDesc()
				{
					GridSize = 5,
					MaximumMotionDistance = 2,
					ProjectionPlaneNormal = new Vector3(0, 1, 0),
					MaximumParticles = 1000
				};

				ParticleSystem particleSystem;
				using (particleSystem = physics.CreateParticleSystem(desc))
				{
					GC.Collect();

					Assert.IsFalse(particleSystem.Disposed);
					Assert.IsTrue(ObjectTable.Contains(particleSystem));
				}

				Assert.IsTrue(particleSystem.Disposed);
			}
		}
	}
}