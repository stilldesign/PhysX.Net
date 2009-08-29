using System;
using System.Linq;
using System.Collections.Generic;
using Microsoft.VisualStudio.TestTools.UnitTesting;
#if GRAPHICS_XNA31
using Microsoft.Xna.Framework;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class ActorTests : TestBase
	{
		public ActorTests()
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
		public void ActorDeletion()
		{
			using( CreateCoreAndScene() )
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
				};

				Actor actor = this.Scene.CreateActor( actorDesc );

				actor.Dispose();
			}
		}

		[TestMethod]
		public void DeletePairedActors()
		{
			using( CreateCoreAndScene() )
			{
				Actor actorA, actorB;
				{
					ActorDescription actorDesc = new ActorDescription()
					{
						Shapes = { new BoxShapeDescription( 5, 6, 7 ) }
					};

					actorA = this.Scene.CreateActor( actorDesc );
				}
				{
					ActorDescription actorDesc = new ActorDescription()
					{
						Shapes = { new BoxShapeDescription( 2, 5, 7 ) }
					};

					actorB = this.Scene.CreateActor( actorDesc );
				}

				this.Scene.SetActorPairFlags( actorA, actorB, ContactPairFlag.All );
				ContactPairFlag pairFlags = this.Scene.GetActorPairFlags( actorA, actorB );

				actorB.Dispose();
				actorA.Dispose();
			}
		}

		[TestMethod]
		public void RequiredMassSpaceInertia()
		{
			var shapeDescription = new SphereShapeDescription( 5 );
			shapeDescription.Flags |= ( ShapeFlag.TriggerOnEnter | ShapeFlag.TriggerOnLeave );

			var actorDesc = new ActorDescription()
			{
				BodyDescription = new BodyDescription( 1 )
				{
					MassSpaceInertia = new Vector3( 1, 1, 1 ),
					BodyFlags = BodyFlag.Kinematic
				},
				Shapes = { shapeDescription }
			};

			Assert.IsTrue( actorDesc.IsValid() );
		}
	}
}
