using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	partial class FluidBlob
	{
		private void LoadPhysics()
		{
			// Create a simple fluid description with fluids and visualization enabled
			FluidDescription fluidDesc = new FluidDescription()
			{
				Flags = FluidFlag.Enabled | FluidFlag.Visualization,
			};

			// Store our particle positions somewhere (as our particle generation function below generates and unknown number of particles at runtime we need a list instead of an array)
			var particlePositions = new List<Vector3>();

			// Move all the particles by this offset
			Vector3 position = new Vector3( 0, 20, 0 );

			// Number of particles in the x, y and z directions
			int sideNum = 10;
			float distance = 1f;

			float radius = sideNum * distance * 0.5f;

			for( int i = 0; i < sideNum; i++ )
			{
				for( int j = 0; j < sideNum; j++ )
				{
					for( int k = 0; k < sideNum; k++ )
					{
						Vector3 p = new Vector3( i * distance, j * distance, k * distance );

						if( ( p - new Vector3( radius, radius, radius ) ).Length() < radius )
						{
							p += position - new Vector3( radius, radius, radius );

							particlePositions.Add( p );
						}
					}
				}
			}

			// Allocate memory for the initial particle positions to be stored in
			// And then set the position buffer
			fluidDesc.InitialParticleData.AllocatePositionBuffer<Vector3>( particlePositions.Count );
			fluidDesc.InitialParticleData.NumberOfParticles = particlePositions.Count;
			fluidDesc.InitialParticleData.PositionBuffer.SetData( particlePositions.ToArray() );

			// Allocate memory for PhysX to store the position of each particle
			fluidDesc.ParticleWriteData.AllocatePositionBuffer<Vector3>( particlePositions.Count );
			fluidDesc.ParticleWriteData.NumberOfParticles = particlePositions.Count;

			Fluid fluid = this.Engine.Scene.CreateFluid( fluidDesc );

			//

			// Make a basic box (ramp) for the particle to slide down
			ActorDescription rampDesc = new ActorDescription()
			{
				Shapes = { new BoxShapeDescription( 10, 0.2f, 10 ) },
				GlobalPose =
					Matrix.RotationZ( 0.3f ) *
					Matrix.Translation( 0, 5, 0 )
			};

			Actor ramp = this.Engine.Scene.CreateActor( rampDesc );
		}
	}
}