using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

using Microsoft.Xna.Framework;

using StillDesign.PhysX;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class Joints
	{
		public Joints()
		{

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
		public void CreateDistanceJoint()
		{
			Core core = new Core();

			var scene = core.CreateScene();

			Actor actorA, actorB;
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = new BodyDescription( 20 ),
					Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
				};

				actorA = scene.CreateActor( actorDesc );
			}
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = new BodyDescription( 20 ),
					Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
				};

				actorB = scene.CreateActor( actorDesc );
			}

			DistanceJointDescription distanceJointDesc = new DistanceJointDescription()
			{
				Actor1 = actorA,
				Actor2 = actorB
			};

			var distanceJoint = scene.CreateJoint( distanceJointDesc ) as DistanceJoint;

			Assert.IsNotNull( distanceJoint );

			scene.Simulate( 1.0f / 60.0f );
		}

		[TestMethod]
		public void ReleaseJoint()
		{
			Core core = new Core();

			var scene = core.CreateScene();

			Actor actorA, actorB;
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = new BodyDescription( 20 ),
					Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
				};

				actorA = scene.CreateActor( actorDesc );
			}
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = new BodyDescription( 20 ),
					Shapes = { new BoxShapeDescription( 2, 5, 7 ) }
				};

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

			d6.Dispose();
		}
	}
}