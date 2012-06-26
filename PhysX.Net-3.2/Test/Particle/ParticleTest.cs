using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class ParticleTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeParticleSystemInstance()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				ParticleSystem particleSystem;
				using (particleSystem = physics.Physics.CreateParticleSystem(100))
				{
					GC.Collect();

					Assert.IsFalse(particleSystem.Disposed);
					Assert.IsTrue(ObjectTable.Contains(particleSystem));
				}

				Assert.IsTrue(particleSystem.Disposed);
			}
		}

		[TestMethod]
		public void CreateAndDisposeParticleFluid()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				ParticleSystem particleSystem = physics.Physics.CreateParticleSystem(100);

				ParticleFluid fluid = physics.Physics.CreateParticleFluid(100);

				Assert.IsTrue(ObjectTable.Contains(fluid));

				Assert.IsFalse(fluid.Disposed);

				fluid.Dispose();

				Assert.IsTrue(fluid.Disposed);
			}
		}
	}
}