using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StillDesign.PhysX.Tests
{
	[TestClass]
	public class CoreTests : TestBase
	{
		public CoreTests()
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
		public void CoreCreation()
		{
			Core core = new Core();

			Assert.IsTrue( core != null );

			core.Dispose();
		}

		[TestMethod]
		public void DisposeCore()
		{
			{
				ConsoleOutputStream consoleOutputStream = new ConsoleOutputStream();

				Core core = new Core( new CoreDescription(), consoleOutputStream );

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

				core.Dispose();
			}

			{
				ConsoleOutputStream consoleOutputStream = new ConsoleOutputStream();

				Core core = new Core( new CoreDescription(), consoleOutputStream );

				Scene scene = core.CreateScene();

				Actor actorA, actorB;
				{
					ActorDescription actorDesc = new ActorDescription();

					actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

					actorA = scene.CreateActor( actorDesc );
				}

				core.Dispose();
			}
		}

		[TestMethod]
		public void CreatingTwoCoresCausesException()
		{
			Core core1 = new Core();

			try
			{
				Core core2 = new Core();
				Assert.Fail();
			}catch( PhysXException ){

			}

			core1.Dispose();
		}

		[TestMethod]
		public void Parameter()
		{
			using( CreateCoreAndScene() )
			{
				this.Core.SetParameter( PhysicsParameter.DefaultSleepLinearVelocitySquared, 0.14f * 0.14f );
				this.Core.SetParameter( PhysicsParameter.DefaultSleepAngularVelocitySquared, 0.15f * 0.15f );

				Assert.IsTrue( IsWithinTolerance( this.Core.GetParameter( PhysicsParameter.DefaultSleepLinearVelocitySquared ), 0.14f * 0.14f ) );
				Assert.IsTrue( IsWithinTolerance( this.Core.GetParameter( PhysicsParameter.DefaultSleepAngularVelocitySquared ), 0.15f * 0.15f ) );
			}
		}
		private bool IsWithinTolerance( float value, float compare )
		{
			const float epsilon = 0.01f;

			return ( value > compare - epsilon ) && ( value < compare + epsilon );
		}

		[TestMethod]
		public void RuntimeFileChecks()
		{
			Type runtimeFileChecksType = Type.GetType( "StillDesign.PhysX.RuntimeFileChecks" );

			
		}
	}
}