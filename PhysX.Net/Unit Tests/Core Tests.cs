using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StillDesign.PhysX.UnitTests
{
	/// <summary>
	/// Summary description for Core_Tests
	/// </summary>
	[TestClass]
	public class CoreTests : TestBase
	{
		public CoreTests()
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

			bool threw = false;
			try
			{
				Core core2 = new Core();
			}catch( PhysXException ){
				threw = true;
			}

			Assert.IsTrue( threw );

			core1.Dispose();
		}
	}
}
