using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.JointsSample
{
	public class JointsSample : Sample
	{
		public JointsSample()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var material = scene.Physics.CreateMaterial(0.7f, 0.7f, 0.1f);

			// Spherical Joint
			{
				// Actor 0
				var rigidActor0 = scene.Physics.CreateRigidDynamic();
				rigidActor0.CreateShape(new BoxGeometry(2, 2, 2), material);

				rigidActor0.GlobalPose = Matrix.Translation(0, 10, 0);
				rigidActor0.SetMassAndUpdateInertia(10);



				// Actor 1
				//var rigidActor1 = scene.Physics.CreateRigidDynamic();
				//rigidActor1.CreateShape(new BoxGeometry(2, 2, 2), material);

				//rigidActor1.GlobalPose = Matrix.Translation(-20, 10, 0);
				//rigidActor1.SetMassAndUpdateInertia(10);

				//rigidActor1.Flags = RigidDynamicFlags.Kinematic; // Pin this actor in space

				//scene.AddActor(rigidActor1);

				//

				var sphericalJoint = scene.CreateJoint<SphericalJoint>(rigidActor0, Matrix.Translation(0, 4, 0), null, Matrix.Translation(0, 15, 0));

				sphericalJoint.ConstraintFlag = ConstraintFlag.Visualization;

				scene.AddActor(rigidActor0);
			}
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}