using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using PhysX;
using PhysX.Samples;

namespace DoublePendulumSample
{
	public class DoublePendulumSample : Sample
	{
		private RigidDynamic _sphereC;

		public DoublePendulumSample()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(PhysX.Scene scene)
		{
			var material = scene.Physics.CreateMaterial(0.7f, 0.7f, 0.1f);

			var sphereA = scene.Physics.CreateRigidDynamic();
			sphereA.CreateShape(new SphereGeometry(1), material);
			sphereA.GlobalPose = Matrix4x4.CreateTranslation(0, 30, 0);

			scene.AddActor(sphereA);

			//

			var sphereB = scene.Physics.CreateRigidDynamic();
			sphereB.CreateShape(new SphereGeometry(1), material);
			sphereB.GlobalPose = Matrix4x4.CreateTranslation(0, 40, 0);

			scene.AddActor(sphereB);

			//

			var sphereC = scene.Physics.CreateRigidDynamic();
			sphereC.CreateShape(new SphereGeometry(1), material);
			sphereC.GlobalPose = Matrix4x4.CreateTranslation(0, 50, 0);

			scene.AddActor(sphereC);

			_sphereC = sphereC;

			//

			var revoluteABJoint = scene.CreateJoint<RevoluteJoint>(sphereA, Matrix4x4.Identity, sphereB, Matrix4x4.Identity);
			revoluteABJoint.SetGlobalFrame(new Vector3(0, 35, 0), new Vector3(0, 0, 1));
			revoluteABJoint.ConstraintFlags = ConstraintFlag.Visualization;

			var revoluteBCJoint = scene.CreateJoint<RevoluteJoint>(sphereB, Matrix4x4.Identity, sphereC, Matrix4x4.Identity);
			revoluteBCJoint.SetGlobalFrame(new Vector3(0, 45, 0), new Vector3(0, 0, 1));
			revoluteBCJoint.ConstraintFlags = ConstraintFlag.Visualization;

			var revoluteAJoint = scene.CreateJoint<RevoluteJoint>(sphereA, Matrix4x4.Identity, null, Matrix4x4.Identity);
			revoluteAJoint.SetGlobalFrame(new Vector3(0, 30, 0), new Vector3(0, 0, 1));
			revoluteAJoint.ConstraintFlags = ConstraintFlag.Visualization;
		}

		protected override void Update(TimeSpan elapsed)
		{
			
		}

		protected override void Draw()
		{
		}

		protected override void ProcessKeyboard(Key[] pressedKeys)
		{
			if (pressedKeys.Contains(Key.P))
			{
				_sphereC.AddForceAtLocalPosition(new Vector3(25, 0, 0), new Vector3(0, 0, 0));
			}

			base.ProcessKeyboard(pressedKeys);
		}
	}
}
