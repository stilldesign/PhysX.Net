using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Tests
{
	[TestClass]
	public class ActorTests : TestBase
	{
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
