using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class FluidTests : TestBase
	{
		[TestMethod]
		public void DisposeOfFluid()
		{
			using( CreateCoreAndScene() )
			{
				const int numberOfParticles = 100;

				FluidDescription fluidDescription = new FluidDescription()
				{
					Flags = FluidFlag.Enabled | FluidFlag.Visualization
				};

				Random random = new Random();

				fluidDescription.InitialParticleData.AllocatePositionBuffer<Vector3>( numberOfParticles );
				for( int i = 0; i < numberOfParticles; i++ )
				{
					float x = (float)random.NextDouble();
					float y = (float)random.NextDouble();
					float z = (float)random.NextDouble();

					fluidDescription.InitialParticleData.PositionBuffer.Write( new Vector3( x, y, z ) * 50 );
				}

				fluidDescription.InitialParticleData.NumberOfParticles = numberOfParticles;

				fluidDescription.IsValid();
				Fluid fluid = this.Scene.CreateFluid( fluidDescription );

				fluid.Dispose();
			}
		}
	}
}