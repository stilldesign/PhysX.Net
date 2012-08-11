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
				var box = scene.Physics.CreateRigidDynamic();
				box.CreateShape(new BoxGeometry(2, 2, 2), material);
				box.GlobalPose = Matrix.Translation(0, 10, 0);
				box.SetMassAndUpdateInertia(10);

				//

				var sphericalJoint = scene.CreateJoint<SphericalJoint>(box, Matrix.Translation(0, 4, 0), null, Matrix.Translation(0, 15, 0));
				sphericalJoint.ConstraintFlag = ConstraintFlag.Visualization;

				scene.AddActor(box);
			}

			// Revolute Joint
			{
				var box = scene.Physics.CreateRigidDynamic();
				box.CreateShape(new BoxGeometry(2, 2, 2), material);
				box.GlobalPose = Matrix.Translation(-10, 10, 0);
				box.SetMassAndUpdateInertia(10);

				//

				var revoluteJoint = scene.CreateJoint<RevoluteJoint>(box, Matrix.Translation(0, 4, 0), null, Matrix.Translation(-10, 15, 0));
				revoluteJoint.ConstraintFlag = ConstraintFlag.Visualization;

				scene.AddActor(box);
			}

			// Breakable Revolute Joint
			{
				var box = scene.Physics.CreateRigidDynamic();
				box.CreateShape(new BoxGeometry(2, 2, 2), material);
				box.GlobalPose = Matrix.Translation(10, 10, 0);
				box.SetMassAndUpdateInertia(10);

				//

				var revoluteJoint = scene.CreateJoint<RevoluteJoint>(box, Matrix.Translation(0, 4, 0), null, Matrix.Translation(10, 15, 0));
				revoluteJoint.ConstraintFlag = ConstraintFlag.Visualization;
				revoluteJoint.BreakForce = 0.001f;

				scene.AddActor(box);
			}

			// Distance Joint
			{
				var box = scene.Physics.CreateRigidDynamic();
				box.CreateShape(new BoxGeometry(2, 2, 2), material);
				box.GlobalPose = Matrix.Translation(-20, 10, 0);
				box.SetMassAndUpdateInertia(10);

				//

				var distanceJoint = scene.CreateJoint<DistanceJoint>(box, Matrix.Translation(0, 4, 0), null, Matrix.Translation(-20, 15, 0));
				distanceJoint.ConstraintFlag = ConstraintFlag.Visualization;
				distanceJoint.MinimumDistance = 1;
				distanceJoint.MaximumDistance = 3;

				scene.AddActor(box);
			}

			// Fixed Joint
			{
				var box = scene.Physics.CreateRigidDynamic();
				box.CreateShape(new BoxGeometry(2, 2, 2), material);
				box.GlobalPose = Matrix.Translation(-30, 15, 0);
				box.SetMassAndUpdateInertia(10);

				//

				var fixedJoint = scene.CreateJoint<FixedJoint>(box, Matrix.Identity, null, Matrix.Translation(-30, 15, 0));
				fixedJoint.ConstraintFlag = ConstraintFlag.Visualization;

				scene.AddActor(box);
			}

			// Prismatic Joint
			{
				var box = scene.Physics.CreateRigidDynamic();
				box.CreateShape(new BoxGeometry(2, 2, 2), material);
				box.GlobalPose = Matrix.Translation(-40, 15, 0);
				box.SetMassAndUpdateInertia(10);

				//

				var prismaticJoint = scene.CreateJoint<PrismaticJoint>(box, Matrix.Identity, null, Matrix.Translation(-40, 15, 0));
				prismaticJoint.ConstraintFlag = ConstraintFlag.Visualization;

				scene.AddActor(box);
			}

			// D6 Joint
			{
				var box = scene.Physics.CreateRigidDynamic();
				box.CreateShape(new BoxGeometry(2, 2, 2), material);
				box.GlobalPose = Matrix.Translation(20, 15, 0);
				box.SetMassAndUpdateInertia(10);

				//

				var d6Joint = scene.CreateJoint<D6Joint>(box, Matrix.Identity, null, Matrix.Translation(20, 15, 0));
				d6Joint.ConstraintFlag = ConstraintFlag.Visualization;
				d6Joint.SetMotion(D6Axis.Twist, D6Motion.Free); // Spin on the X axis

				scene.AddActor(box);
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