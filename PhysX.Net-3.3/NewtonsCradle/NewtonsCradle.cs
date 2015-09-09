using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Threading.Tasks;
using System.Windows.Input;
using PhysX.Samples;

namespace PhysX.Samples.NewtonsCradle
{
	public class NewtonsCradle : Sample
	{
		private RigidDynamic[] _balls;

		public NewtonsCradle()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			scene.SetVisualizationParameter(VisualizationParameter.JointLocalFrames, true);

			//

			const int balls = 5;
			const float
				r = 2,
				d = r * 2,
				offGround = 2;

			_balls = new RigidDynamic[balls];

			var ballMaterial = scene.Physics.CreateMaterial(0, 0, 0);

			for (int i = 0; i < balls; i++)
			{
				var ballGeom = new SphereGeometry(r);

				var ball = scene.Physics.CreateRigidDynamic();
				ball.CreateShape(ballGeom, ballMaterial);

				Vector3 position = new Vector3(r + (i * d) - (balls * d * 0.5f), r + offGround, 0);

				ball.GlobalPose = Matrix4x4.CreateTranslation(position);
				ball.AngularDamping = 0;
				ball.LinearDamping = 0;
				ball.MaxAngularVelocity = 100;
				ball.SetMassAndUpdateInertia(25);

				scene.AddActor(ball);
				
				//

				var jointA = scene.CreateJoint<SphericalJoint>(null, Matrix4x4.Identity, ball, Matrix4x4.Identity);
				jointA.SetGlobalFrame(position + new Vector3(0, 10, 0), new Vector3(0, 0, 1));

				//var jointB = scene.CreateJoint<SphericalJoint>(null, Matrix4x4.Identity, ball, Matrix4x4.Identity);
				//jointB.SetGlobalFrame(position + new Vector3(0, 10, -10), new Vector3(1, 0, 0));

				_balls[i] = ball;
			}
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}

		protected override void ProcessKeyboard(Key[] pressedKeys)
		{
			if (pressedKeys.Contains(Key.K))
			{
				_balls[0].AddLocalForceAtLocalPosition(new Vector3(-2000, 0, 0), new Vector3(0, 0, 0));
			}
		}
	}
}
