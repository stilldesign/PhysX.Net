using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;

namespace PhysX.Test
{
	[TestClass]
	public class ParticleFluidTest : Test
	{
		private PhysicsAndSceneTestUnit _physics;
		private ParticleFluid _fluid;

		[TestInitialize]
		public void TestInitalize()
		{
			_physics = CreatePhysicsAndScene();

			ParticleSystem particleSystem = _physics.Physics.CreateParticleSystem(100);

			_fluid = _physics.Physics.CreateParticleFluid(100);
		}
		[TestCleanup]
		public void TestCleanup()
		{
			_physics.Dispose();
			_physics = null;

			_fluid = null;
		}

		[TestMethod]
		public void GetStiffness()
		{
			_fluid.Stiffness = 100;

			Assert.AreEqual(100, _fluid.Stiffness);
		}

		[TestMethod]
		public void GetViscosity()
		{
			_fluid.Viscosity = 4;

			Assert.AreEqual(4, _fluid.Viscosity);
		}

		[TestMethod]
		public void GetSetRestParticleDistance()
		{
			_fluid.RestParticleDistance = 3.3f;

			Assert.AreEqual(3.3f, _fluid.RestParticleDistance);
		}


		[TestMethod]
		public void GetSetExternalAcceleration()
		{
			_fluid.ExternalAcceleration = new Vector3(9, 7, 1);

			Assert.AreEqual(new Vector3(9, 7, 1), _fluid.ExternalAcceleration);
		}

		[TestMethod]
		public void GetSetParticleMass()
		{
			_fluid.ParticleMass = 55;

			Assert.AreEqual(55, _fluid.ParticleMass);
		}

		[TestMethod]
		public void GetSetRestitution()
		{
			_fluid.Restitution = 0.2f;

			Assert.AreEqual(0.2f, _fluid.Restitution);
		}

		[TestMethod]
		public void GetSetDynamicFriction()
		{
			_fluid.DynamicFriction = 0.11f;

			Assert.AreEqual(0.11f, _fluid.DynamicFriction);
		}

		[TestMethod]
		public void GetSetStaticFriction()
		{
			_fluid.StaticFriction = 11;

			Assert.AreEqual(11, _fluid.StaticFriction);
		}

		[TestMethod]
		public void GetMaximumParticles()
		{
			// Maximum particles is initalized in the constructor
			Assert.AreEqual(100, _fluid.MaximumParticles);
		}

		[TestMethod]
		public void SetPositions()
		{
			var positions = new Vector3[100];
			for (int i = 0; i < 100; i++)
			{
				positions[i] = new Vector3(i, i, i);
			}

			var indices = new int[100];
			for (int i = 0; i < 100; i++)
			{
				indices[i] = i;
			}

			_fluid.SetPositions(positions, indices);
		}
	}
}