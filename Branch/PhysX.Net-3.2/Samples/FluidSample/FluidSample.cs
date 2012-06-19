using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.FluidSample
{
	public class FluidSample : Sample
	{
		public FluidSample()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			CreateFluidBlob(scene);
			CreateFunnel(scene);
		}

		private static void CreateFluidBlob(Scene scene)
		{
			// The number of particles we want along one of the three dimensions
			const int d = 15;

			// Create the particle fluid
			var particleFluid = scene.Physics.CreateParticleFluid(d * d * d);

			particleFluid.RestParticleDistance *= 10.5f;

			//

			// Create an array to hold the positions of the particles
			var particlePositions = new Vector3[particleFluid.MaximumParticles];

			var blobOffset = -new Vector3(d) * 0.5f;

			int i = 0;
			for (int x = 0; x < d; x++)
			{
				for (int y = 0; y < d; y++)
				{
					for (int z = 0; z < d; z++)
					{
						// Compute the location in a grid of particles + move the grid back so its center is at 0, 0, 0
						particlePositions[i++] = new Vector3(x, 20 + y, z) + blobOffset;
					}
				}
			}

			// Add the particles
			var particleCreateDesc = new ParticleCreationData()
			{
				NumberOfParticles = particleFluid.MaximumParticles,
				PositionBuffer = particlePositions,
				IndexBuffer = Enumerable.Range(0, particlePositions.Length).ToArray()
			};

			int numCreated = particleFluid.CreateParticles(particleCreateDesc);

			scene.AddActor(particleFluid);
		}

		private void CreateFunnel(Scene scene)
		{
			// Create two boxes that angle inwards to create a funnel

			var material = scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var rigidActor = scene.Physics.CreateRigidDynamic();

			var boxGeom = new BoxGeometry(10, 0.25f, 5);
			var boxShape = rigidActor.CreateShape(boxGeom, material);

			rigidActor.GlobalPose =
				Matrix.RotationX(0.2f) *
				Matrix.Translation(0, 7, -5.1f);
			rigidActor.SetMassAndUpdateInertia(10);
			rigidActor.Flags = RigidDynamicFlags.Kinematic;

			scene.AddActor(rigidActor);

			//

			var rigidActor2 = scene.Physics.CreateRigidDynamic();

			var boxGeom2 = new BoxGeometry(10, 0.25f, 5);
			var boxShape2 = rigidActor2.CreateShape(boxGeom2, material);

			rigidActor2.GlobalPose =
				Matrix.RotationX(-0.2f) *
				Matrix.Translation(0, 7, 5.1f);
			rigidActor2.SetMassAndUpdateInertia(10);
			rigidActor2.Flags = RigidDynamicFlags.Kinematic;

			scene.AddActor(rigidActor2);
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}