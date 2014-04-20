using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class JointSample
	{
		public static RevoluteJoint RevoluteJoint(Scene scene)
		{
			BoxShapeDescription boxShapeDescA = new BoxShapeDescription(3, 3, 3);
			BoxShapeDescription boxShapeDescB = new BoxShapeDescription(3, 3, 3);

			ActorDescription actorDescA = new ActorDescription()
			{
				BodyDescription = new BodyDescription(10.0f),
				GlobalPose = Matrix.Translation(75, 1.5f, -55),
				Shapes = { boxShapeDescA }
			};
			Actor actorA = scene.CreateActor(actorDescA);

			ActorDescription actorDescB = new ActorDescription()
			{
				BodyDescription = new BodyDescription(10.0f),
				GlobalPose = Matrix.Translation(70, 1.5f, -55),
				Shapes = { boxShapeDescB }
			};
			Actor actorB = scene.CreateActor(actorDescB);

			//

			RevoluteJointDescription revoluteJointDesc = new RevoluteJointDescription()
			{
				Actor1 = actorA,
				Actor2 = actorB,
				Motor = new MotorDescription(20, 20.1f, true)
			};
			revoluteJointDesc.Flags |= RevoluteJointFlag.MotorEnabled;
			revoluteJointDesc.SetGlobalAnchor(new Vector3(73.5f, 1.5f, -55));
			revoluteJointDesc.SetGlobalAxis(new Vector3(1, 0, 0));

			RevoluteJoint revoluteJoint = scene.CreateJoint(revoluteJointDesc) as RevoluteJoint;

			return revoluteJoint;
		}

		public static PrismaticJoint PrismaticJointWithLimit(Scene scene)
		{
			Actor actorA, actorB;
			{
				BoxShapeDescription boxShapeDesc = new BoxShapeDescription(3, 3, 3);

				BodyDescription bodyDesc = new BodyDescription(10.0f);
				bodyDesc.BodyFlags |= BodyFlag.Kinematic;

				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = bodyDesc,
					GlobalPose = Matrix.Translation(70, 25, -65),
					Shapes = { boxShapeDesc }
				};
				actorA = scene.CreateActor(actorDesc);
			}
			{
				BoxShapeDescription boxShapeDesc = new BoxShapeDescription(3, 3, 3);

				ActorDescription actorDesc = new ActorDescription()
				{
					BodyDescription = new BodyDescription(10.0f),
					GlobalPose = Matrix.Translation(70, 15, -65),
					Shapes = { boxShapeDesc }
				};
				actorB = scene.CreateActor(actorDesc);
			}

			PrismaticJointDescription prismaticJointDesc = new PrismaticJointDescription()
			{
				Actor1 = actorA,
				Actor2 = actorB,
			};
			prismaticJointDesc.SetGlobalAnchor(new Vector3(70, 20, -65));
			prismaticJointDesc.SetGlobalAxis(new Vector3(0, 1, 0));

			PrismaticJoint prismaticJoint = scene.CreateJoint(prismaticJointDesc) as PrismaticJoint;

			LimitPlane limitPlane = new LimitPlane(new Vector3(0, 1, 0), new Vector3(-30, 8, -30), 0);
			prismaticJoint.AddLimitPlane(limitPlane);

			return prismaticJoint;
		}
	}
}