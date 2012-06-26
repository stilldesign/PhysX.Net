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

				var material = scene.Physics.CreateMaterial(0.7f, 0.7f, 0.1f);

				var boxGeom = new BoxGeometry(2, 2, 2);
				var boxShape = rigidActor.CreateShape(boxGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(0, 10 + i * boxGeom.Size.Y, 0);
				rigidActor.SetMassAndUpdateInertia(10);

				scene.AddActor(rigidActor);
			}
		}
	}
}