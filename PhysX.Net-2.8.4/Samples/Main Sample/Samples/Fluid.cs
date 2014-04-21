using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class FluidSample
	{
		public static PhysX.Fluid FluidWithEmitterAndDrain(Scene scene)
		{
			const int maximumParticles = 1000;

			var fluidEmitterDesc = new FluidEmitterDescription()
			{
				DimensionX = 0.5f,
				DimensionY = 0.5f,
				Rate = 15,
				RelativePose = 
					Matrix.RotationAxis(new Vector3(0, 1, 0), (float)Math.PI) *
					Matrix.Translation(-40, 10, -50),
				Shape = EmitterShape.Rectangular,
				Type = EmitterType.ConstantFlowRate,
				RandomAngle = 0.5f
			};
			fluidEmitterDesc.Flags |= (FluidEmitterFlag.Enabled | FluidEmitterFlag.Visualization);

			var fluidDesc = new FluidDescription()
			{
				Emitters = { fluidEmitterDesc },
				Flags = FluidFlag.Enabled | FluidFlag.Visualization,
				MaximumParticles = maximumParticles
			};
			fluidDesc.ParticleWriteData.AllocatePositionBuffer<Vector3>(maximumParticles);
			fluidDesc.ParticleWriteData.NumberOfParticles = maximumParticles;

			var fluid = scene.CreateFluid(fluidDesc);

			// Ledge
			{
				var boxShapeDesc = new BoxShapeDescription(5, 0.1f, 5);

				var drainActorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.RotationX(-0.5f) * Matrix.Translation(-40, 5, -52),
					Shapes = { boxShapeDesc }
				};

				var drianActor = scene.CreateActor(drainActorDesc);
			}

			// Drain
			{
				var boxShapeDesc = new BoxShapeDescription(5, 0.1f, 5);
				boxShapeDesc.Flags |= ShapeFlag.FluidDrain;

				var drainActorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.Translation(-40, 0, -55),
					Shapes = { boxShapeDesc }
				};

				var drianActor = scene.CreateActor(drainActorDesc);
			}

			return fluid;
		}
	}
}