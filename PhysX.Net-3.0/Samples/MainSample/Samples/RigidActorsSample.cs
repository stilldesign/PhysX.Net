using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples
{
	public static class RigidActorsSample
	{
		public static void StackOfBoxes(Scene scene)
		{
			for (int i = 0; i < 10; i++)
			{
				var rigidActor = scene.Physics.CreateRigidDynamic();

				var material = scene.Physics.CreateMaterial(0.4f, 0.1f, 0.2f);

				var boxGeom = new BoxGeometry(5, 5, 5);
				var boxShape = rigidActor.CreateShape(boxGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(0, 10 + i * boxGeom.Size.Y, 0);
			}
		}
	}
}