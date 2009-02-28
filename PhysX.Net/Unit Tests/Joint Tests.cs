using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

#if GRAPHICS_XNA2 || GRAPHICS_XNA3
using Microsoft.Xna.Framework;
#elif GRAPHICS_MDX
using Microsoft.DirectX;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

using StillDesign.PhysX;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class JointTests : TestBase
	{
		public JointTests()
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
			using( CreateCoreAndScene() )
			{
				Actor actorA, actorB;
				{
					ActorDescription actorDesc = new ActorDescription()
					{
						BodyDescription = new BodyDescription( 20 ),
						Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
					};

					actorA = this.Scene.CreateActor( actorDesc );
				}
				{
					ActorDescription actorDesc = new ActorDescription()
					{
						BodyDescription = new BodyDescription( 20 ),
						Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
					};

					actorB = this.Scene.CreateActor( actorDesc );
				}

				DistanceJointDescription distanceJointDesc = new DistanceJointDescription()
				{
					Actor1 = actorA,
					Actor2 = actorB
				};

				var distanceJoint = this.Scene.CreateJoint( distanceJointDesc ) as DistanceJoint;

				Assert.IsNotNull( distanceJoint );

				Update();
			}
		}

		[TestMethod]
		public void ReleaseJoint()
		{
			using( CreateCoreAndScene() )
			{
				Actor actorA, actorB;
				{
					ActorDescription actorDesc = new ActorDescription()
					{
						BodyDescription = new BodyDescription( 20 ),
						Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
					};

					actorA = this.Scene.CreateActor( actorDesc );
				}
				{
					ActorDescription actorDesc = new ActorDescription()
					{
						BodyDescription = new BodyDescription( 20 ),
						Shapes = { new BoxShapeDescription( 2, 5, 7 ) }
					};

					actorB = this.Scene.CreateActor( actorDesc );
				}

				D6JointDescription d6JointDesc = new D6JointDescription()
				{
					Actor1 = actorA,
					Actor2 = actorB
				};

				d6JointDesc.SetGlobalAnchor( new Vector3( 5, 6, 7 ) );
				d6JointDesc.SetGlobalAxis( new Vector3( 0, 0, 1 ) );

				D6Joint d6 = this.Scene.CreateJoint( d6JointDesc ) as D6Joint;

				d6.Dispose();
			}
		}

		[TestMethod]
		public void DisposalOfJointedActor()
		{
			using( CreateCoreAndScene() )
			{
				Actor actorA, actorB;
				{
					ActorDescription actorDesc = new ActorDescription();
					actorDesc.BodyDescription = new BodyDescription( 20 );

					actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

					actorA = this.Scene.CreateActor( actorDesc );
				}
				{
					ActorDescription actorDesc = new ActorDescription();
					actorDesc.BodyDescription = new BodyDescription( 20 );

					actorDesc.Shapes.Add( new BoxShapeDescription( 2, 5, 7 ) );

					actorB = this.Scene.CreateActor( actorDesc );
				}

				D6JointDescription d6JointDesc = new D6JointDescription()
				{
					Actor1 = actorA,
					Actor2 = actorB
				};

				d6JointDesc.SetGlobalAnchor( new Vector3( 5, 6, 7 ) );
				d6JointDesc.SetGlobalAxis( new Vector3( 0, 0, 1 ) );

				D6Joint d6 = this.Scene.CreateJoint( d6JointDesc ) as D6Joint;

				actorA.Dispose();
				d6.Dispose();
			}
		}
	}
}