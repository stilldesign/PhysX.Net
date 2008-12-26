using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StillDesign.PhysX.UnitTests
{
	/// <summary>
	/// Summary description for ActorTests
	/// </summary>
	[TestClass]
	public class ActorTests : TestBase
	{
		public ActorTests()
		{
			//
			// TODO: Add constructor logic here
			//
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
		public void ActorDeletion()
		{
			ActorDescription actorDesc = new ActorDescription();

			actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

			Actor actor = this.Scene.CreateActor( actorDesc );

			actor.Dispose();
		}

		[TestMethod]
		public void DeletePairedActors()
		{
			Actor actorA, actorB;
			{
				ActorDescription actorDesc = new ActorDescription();

				actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

				actorA = this.Scene.CreateActor( actorDesc );
			}
			{
				ActorDescription actorDesc = new ActorDescription();

				actorDesc.Shapes.Add( new BoxShapeDescription( 2, 5, 7 ) );

				actorB = this.Scene.CreateActor( actorDesc );
			}

			this.Scene.SetActorPairFlags( actorA, actorB, ContactPairFlag.All );
			ContactPairFlag pairFlags = this.Scene.GetActorPairFlags( actorA, actorB );

			actorB.Dispose();
			actorA.Dispose();
		}
	}
}
