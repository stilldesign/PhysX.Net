using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Tests
{
	[TestClass]
	public class FluidTests : TestBase
	{
		[TestMethod]
		public void DisposeOfFluid()
		{
			using (CreateCoreAndScene())
			{
				const int numberOfParticles = 100;

				FluidDescription fluidDescription = new FluidDescription()
				{
					Flags = FluidFlag.Enabled | FluidFlag.Visualization
				};

				Random random = new Random();

				fluidDescription.InitialParticleData.AllocatePositionBuffer<Vector3>(numberOfParticles);
				for (int i = 0; i < numberOfParticles; i++)
				{
					float x = (float)random.NextDouble();
					float y = (float)random.NextDouble();
					float z = (float)random.NextDouble();

					fluidDescription.InitialParticleData.PositionBuffer.Write(new Vector3(x, y, z) * 50);
				}

				fluidDescription.InitialParticleData.NumberOfParticles = numberOfParticles;

				fluidDescription.IsValid();
				Fluid fluid = this.Scene.CreateFluid(fluidDescription);

				fluid.Dispose();
			}
		}

		[TestMethod]
		public void ParticleWriteData()
		{
			using (CreateCoreAndScene())
			{
				var fluidDesc = new FluidDescription()
				{
					Flags = FluidFlag.Enabled
				};

				int numParticles = 1000;

				fluidDesc.ParticleWriteData.AllocatePositionBuffer<Vector3>(numParticles);
				fluidDesc.ParticleWriteData.NumberOfParticles = numParticles;

				var emitterDesc = new FluidEmitterDescription()
				{
					DimensionX = 0.01f,
					DimensionY = 0.01f,
					MaximumParticles = numParticles,
					Shape = EmitterShape.Ellipse,
					FluidVelocityMagnitude = 0f,
					RandomPosition = new Vector3(1f / 100f, 1f / 100f, 1f / 100f),
				};

				var fluid = this.Scene.CreateFluid(fluidDesc);
				fluid.CreateFluidEmitter(emitterDesc);

				// Advance the scene forward so the emitter has time to emit some particles
				for (int i = 0; i < 100; i++)
				{
					this.Scene.Simulate(1f / 60f);
					this.Scene.FlushStream();
					this.Scene.FetchResults(SimulationStatus.RigidBodyFinished, true);
				}

				// Read the particles
				Vector3[] positions = fluid.ParticleWriteData.PositionBuffer.GetData<Vector3>();

				// There should be a handful particles with positions other than 0, 0, 0
				Assert.AreNotEqual(Vector3.Zero, positions[0]);
				Assert.AreNotEqual(Vector3.Zero, positions[1]);
				Assert.AreNotEqual(Vector3.Zero, positions[2]);
				Assert.AreNotEqual(Vector3.Zero, positions[3]);
				Assert.AreNotEqual(Vector3.Zero, positions[4]);
			}
		}
	}
}