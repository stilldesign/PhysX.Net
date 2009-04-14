using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using Microsoft.Xna.Framework;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class FluidTests : TestBase
	{
		public FluidTests()
		{

		}

		#region Additional test attributes
		//
		// You can use the following additional attributes as you write your tests:
		//
		// Use ClassInitialize to run code before running the first test in the class
		// [ClassInitialize()]
		// public static void MyClassInitialize(TestContext testContext) { }
		//
		// Use ClassCleanup to run code after all tests in a class have run
		// [ClassCleanup()]
		// public static void MyClassCleanup() { }
		//
		// Use TestInitialize to run code before running each test 
		// [TestInitialize()]
		// public void MyTestInitialize() { }
		//
		// Use TestCleanup to run code after each test has run
		// [TestCleanup()]
		// public void MyTestCleanup() { }
		//
		#endregion

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