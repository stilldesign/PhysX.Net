using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Tests
{
	[TestClass]
	public class JointTests : TestBase
	{
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