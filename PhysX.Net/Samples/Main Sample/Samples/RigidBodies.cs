using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class RigidBodySample
	{
		public static void SimpleBoxes(Scene scene)
		{
			for (int x = 0; x < 5; x++)
			{
				BoxShapeDescription boxShapeDesc = new BoxShapeDescription(2, 3, 8);

				ActorDescription actorDesc = new ActorDescription()
				{
					Name = String.Format("Box {0}", x),
					BodyDescription = new BodyDescription(10.0f),
					GlobalPose = Matrix.Translation(100, 15 + 3 * x, 20),
					Shapes = { boxShapeDesc }
				};

				Actor actor = scene.CreateActor(actorDesc);
			}
		}
	}
}