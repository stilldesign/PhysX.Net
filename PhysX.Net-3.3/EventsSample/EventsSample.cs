using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.EventsSample
{
	public class EventsSample : Sample
	{
		public EventsSample()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var material = scene.Physics.CreateMaterial(0.7f, 0.7f, 0.1f);

			var boxA = scene.Physics.CreateRigidDynamic();
			var shapeA = boxA.CreateShape(new BoxGeometry(2, 2, 2), material);
			boxA.GlobalPose = Matrix.Translation(0, 10, 0);

			scene.AddActor(boxA);

			//

			var boxB = scene.Physics.CreateRigidDynamic();
			var shapeB = boxB.CreateShape(new BoxGeometry(2, 2, 2), material);
			boxB.GlobalPose = Matrix.Translation(0, 4, 0);

			scene.AddActor(boxB);

			//

			// Tell PhysX what to call when a contact/touch occurs
			var callback = new EventCallback();
			scene.SetSimulationEventCallback(callback, 0);
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}

	public class EventCallback : SimulationEventCallback
	{
		public override void OnContact(ContactPairHeader pairHeader, ContactPair[] pairs)
		{
			base.OnContact(pairHeader, pairs);
		}
	}
}