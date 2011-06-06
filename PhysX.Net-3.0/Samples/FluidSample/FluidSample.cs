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
			const int d = 100;

			// Create a column of fluid particles
			var desc = new ParticleFluidDesc()
			{
				Flags = ActorFlag.Visualization,
				MaximumParticles = (int)System.Math.Pow(d, 3)
			};

			var particleFluid = scene.Physics.CreateParticleFluid(desc);

			//

			var particlePositions = new Vector3[desc.MaximumParticles];

			int i = 0;
			for (int x = 0; x < d; x++)
			{
				for (int y = 0; y < d; y++)
				{
					for (int z = 0; z < d; z++)
					{
						particlePositions[i++] = new Vector3(x, 20 + y, z);
					}
				}
			}

			var particleCreateDesc = new ParticleCreationData()
			{
				NumberOfParticles = 1000,
				PositionBuffer = particlePositions
			};

			particleFluid.CreateParticles(particleCreateDesc);

			scene.AddActor(particleFluid);
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}