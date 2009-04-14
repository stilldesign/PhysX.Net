using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;

using Microsoft.VisualStudio.TestTools.UnitTesting;

#if GRAPHICS_XNA2 || GRAPHICS_XNA3
using Microsoft.Xna.Framework;
using System.IO;
#elif GRAPHICS_MDX
using Microsoft.DirectX;
using System.IO;
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
			//
			// TODO: Add constructor logic here
			//
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
				ActorDescription actorDesc = new ActorDescription();

				actorDesc.Shapes.Add( new BoxShapeDescription( 5, 6, 7 ) );

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

		[TestMethod]
		public void RequiredMassSpaceInertia()
		{
			var shapeDescription = new SphereShapeDescription( 5 );
			shapeDescription.Flags |= ( ShapeFlag.TriggerOnEnter | ShapeFlag.TriggerOnLeave );

			var actorDesc = new ActorDescription();

			actorDesc.BodyDescription = new BodyDescription( 1 );
			actorDesc.BodyDescription.MassSpaceInertia = new Vector3( 1, 1, 1 );
			actorDesc.BodyDescription.BodyFlags = BodyFlag.Kinematic;

			actorDesc.Shapes.Add( shapeDescription );

			Assert.IsTrue( actorDesc.IsValid() );
		}
	}
}
