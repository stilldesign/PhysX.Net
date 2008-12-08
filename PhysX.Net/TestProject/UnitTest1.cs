using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Diagnostics;

using Microsoft.VisualStudio.TestTools.UnitTesting;

using StillDesign.PhysX;

#if GRAPHICS_MDX
using Microsoft.DirectX;
#elif GRAPHICS_XNA2
using Microsoft.Xna.Framework;
#elif GRAPHICS_XNA3
using Microsoft.Xna.Framework;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No graphics target specified
#endif

namespace TestProject
{
	[TestClass]
	public class UnitTest1
	{
		public UnitTest1()
		{
			
		}

		private TestContext testContextInstance;

		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		public TestContext TestContext
		{
			get
			{
				return testContextInstance;
			}
			set
			{
				testContextInstance = value;
			}
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
		public void CoreCreation()
		{
			Core core = new Core();

			Assert.IsTrue( core != null );
		}

		[TestMethod]
		public void ActorDeletion()
		{
			Core core = new Core();

			Scene scene = core.CreateScene();

			ActorDescription actorDesc = new ActorDescription();

			actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

			Actor actor = scene.CreateActor( actorDesc );

			actor.Dispose();
		}

		[TestMethod]
		public void DeletePairedActors()
		{
			Core core = new Core();

			Scene scene = core.CreateScene();

			Actor actorA, actorB;
			{
				ActorDescription actorDesc = new ActorDescription();

				actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

				actorA = scene.CreateActor( actorDesc );
			}
			{
				ActorDescription actorDesc = new ActorDescription();

				actorDesc.Shapes.Add( new BoxShapeDescription( 2, 5, 7 ) );

				actorB = scene.CreateActor( actorDesc );
			}

			scene.SetActorPairFlags( actorA, actorB, ContactPairFlag.All );
			ContactPairFlag pairFlags = scene.GetActorPairFlags( actorA, actorB );

			actorB.Dispose();
			actorA.Dispose();
		}

		[TestMethod]
		public void DisposeOfFluid()
		{
			Core core = new Core();

			Scene scene = core.CreateScene();

			FluidDescription fluidDescription = new FluidDescription()
			{
				Flags = FluidFlag.Enabled | FluidFlag.Visualization
			};

			Random random = new Random();

			fluidDescription.InitialParticleData.AllocatePositionBuffer<Vector3>( 100 );
			for( int i = 0; i < 100; i++ )
			{
				float x = (float)random.NextDouble();
				float y = (float)random.NextDouble();
				float z = (float)random.NextDouble();

				fluidDescription.InitialParticleData.PositionBuffer.Write( new Vector3( x, y, z ) * 50 );
			}

			Fluid fluid = scene.CreateFluid( fluidDescription );

			fluid.Dispose();
		}

		[TestMethod]
		public void DisposalOfJointedActor()
		{
			Core core = new Core();

			Scene scene = core.CreateScene();

			Actor actorA, actorB;
			{
				ActorDescription actorDesc = new ActorDescription();
				actorDesc.BodyDescription = new BodyDescription( 20 );

				actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

				actorA = scene.CreateActor( actorDesc );
			}
			{
				ActorDescription actorDesc = new ActorDescription();
				actorDesc.BodyDescription = new BodyDescription( 20 );

				actorDesc.Shapes.Add( new BoxShapeDescription( 2, 5, 7 ) );

				actorB = scene.CreateActor( actorDesc );
			}

			D6JointDescription d6JointDesc = new D6JointDescription()
			{
				Actor1 = actorA,
				Actor2 = actorB
			};

			d6JointDesc.SetGlobalAnchor( new Vector3( 5, 6, 7 ) );
			d6JointDesc.SetGlobalAxis( new Vector3( 0, 0, 1 ) );

			D6Joint d6 = scene.CreateJoint( d6JointDesc ) as D6Joint;

			actorA.Dispose();
			d6.Dispose();
		}

		[TestMethod]
		public void DisposeOfBoxController()
		{
			Core core = new Core();

			Scene scene = core.CreateScene();

			var manager = scene.CreateControllerManager();

			var boxControllerDesc = new BoxControllerDescription( 2, 5, 2 )
			{
				
			};

			var boxController = manager.CreateController( boxControllerDesc ) as BoxController;

			boxController.Dispose();

			Debug.Assert( boxController.IsDisposed == true );
			Debug.Assert( manager.Controllers.Count == 0 );
		}
	}
}