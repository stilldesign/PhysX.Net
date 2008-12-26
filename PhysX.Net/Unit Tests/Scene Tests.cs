using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using StillDesign.PhysX;

using Microsoft.Xna.Framework;

using PhysXScene = StillDesign.PhysX.Scene;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class Scene
	{
		private Core _core;
		private PhysXScene _scene;

		public Scene()
		{
			_core = new Core();
			_scene = _core.CreateScene();

			Actor actorA, actorB;
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = new BodyDescription( 20 ),
					GlobalPose = Matrix.CreateTranslation( 0, 0, 10 ),
					Shapes = { new BoxShapeDescription( 5, 5, 5 ) }
				};
				
				actorA = _scene.CreateActor( actorDesc );
			}
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = new BodyDescription( 20 ),
					GlobalPose = Matrix.CreateTranslation( 0, 0, 50 ),
					Shapes = { new BoxShapeDescription( 5, 5, 5 ) }
				};

				actorB = _scene.CreateActor( actorDesc );
			}
		}

		private TestContext testContextInstance;

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
		public void LinearBoxSweep()
		{
			Box box = new Box( new Vector3( 0, 2.5f, 0 ), new Vector3( 5, 5, 5 ) );

			var sweepHits = _scene.LinearObbSweep( box, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object" );

			Assert.IsTrue( sweepHits.Length == 1, "The linear box sweep should of returned 1 hit. Hits returned: {0}", sweepHits.Length );
		}
		[TestMethod]
		public void LinearBoxSweepAllHits()
		{
			Box box = new Box( new Vector3( 0, 2.5f, 0 ), new Vector3( 5, 5, 5 ) );

			var sweepHits = _scene.LinearObbSweep( box, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics | SweepFlags.AllHits, "Dummy Object" );

			Assert.IsTrue( sweepHits.Length == 2, "The linear box sweep should of returned 2 hit. Hits returned: {0}", sweepHits.Length );
		}
		[TestMethod]
		public void LinearBoxSweepCallback()
		{
			Box box = new Box( new Vector3( 0, 2.5f, 0 ), new Vector3( 5, 5, 5 ) );

			SweepCallback callback = new SweepCallback();

			_scene.LinearObbSweep( box, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object", callback );

			Assert.IsTrue( callback.NumberOfHits == 1, "The linear box sweep should of returned 1 hit. Hits returned: {0}", callback.NumberOfHits );
		}

		[TestMethod]
		public void LinearCapsuleSweep()
		{
			Capsule capsule = new Capsule( new Vector3( 0, -5, 0 ), new Vector3( 0, 5, 0 ), 10 );

			var sweepHits = _scene.LinearCapsuleSweep( capsule, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object" );

			Assert.IsTrue( sweepHits.Length == 1, "The linear capsule sweep should of returned 1 hit. Hits returned: {0}", sweepHits.Length );
		}
		[TestMethod]
		public void LinearCapsuleSweepAllHits()
		{
			Capsule capsule = new Capsule( new Vector3( 0, -5, 0 ), new Vector3( 0, 5, 0 ), 10 );

			var sweepHits = _scene.LinearCapsuleSweep( capsule, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics | SweepFlags.AllHits, "Dummy Object" );

			Assert.IsTrue( sweepHits.Length == 2, "The linear capsule sweep should of returned 2 hit. Hits returned: {0}", sweepHits.Length );
		}
		[TestMethod]
		public void LinearCapsuleSweepCallback()
		{
			Capsule capsule = new Capsule( new Vector3( 0, -5, 0 ), new Vector3( 0, 5, 0 ), 10 );

			SweepCallback callback = new SweepCallback();

			_scene.LinearCapsuleSweep( capsule, new Vector3( 0, 0, 1000 ), SweepFlags.Dynamics | SweepFlags.Statics, "Dummy Object", callback );

			Assert.IsTrue( callback.NumberOfHits == 1, "The linear capsule sweep should of returned 1 hit. Hits returned: {0}", callback.NumberOfHits );
		}
	}

	public class SweepCallback : UserEntitySweepQueryHitReport
	{
		public override bool OnEvent( SweepQueryHit[] entities )
		{
			this.NumberOfHits += entities.Length;

			return true;
		}

		public int NumberOfHits
		{
			get;
			private set;
		}
	}
}