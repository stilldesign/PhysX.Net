using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.EventsSample
{
	public class EventsSample : Sample
	{
		public List<Actor> Touched { get; set; }

		public EventsSample()
		{
			this.Touched = new List<Actor>();

			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var material = scene.Physics.CreateMaterial(0.7f, 0.7f, 0.1f);

			var boxA = scene.Physics.CreateRigidDynamic();
			boxA.Name = "Box A";
			boxA.GlobalPose = Matrix.Translation(0, 50, 0);

			var shapeA = boxA.CreateShape(new BoxGeometry(2, 2, 2), material);

			scene.AddActor(boxA);

			//

			var boxB = scene.Physics.CreateRigidDynamic();
			boxB.Name = "Box B";
			boxB.GlobalPose = Matrix.Translation(0, 4, 0);

			var shapeB = boxB.CreateShape(new BoxGeometry(2, 2, 2), material);

			scene.AddActor(boxB);

			//

			// Tell PhysX what to call when a contact/touch occurs
			var callback = new EventCallback(this);
			scene.SetSimulationEventCallback(callback, 0);
		}

		protected override void Update(TimeSpan elapsed)
		{
			// Called after Simulate

			foreach (var touch in this.Touched)
			{
				touch.Dispose();
			}

			this.Touched.Clear();
		}

		protected override void Draw()
		{

		}
	}

	public class EventCallback : SimulationEventCallback
	{
		private EventsSample _sample;

		public EventCallback(EventsSample sample)
		{
			_sample = sample;
		}

		public override void OnContact(ContactPairHeader pairHeader, ContactPair[] pairs)
		{
			base.OnContact(pairHeader, pairs);

			foreach (var pair in pairs)
			{
				// PhysX seems to report the collision of shapes even if we've disposed of them the previous frame, so either could potentially be null
				if (pair.Shape0 != null && pair.Shape1 != null)
				{
					var names = new[] { pair.Shape0.Actor.Name, pair.Shape1.Actor.Name };

					// Delete the actors when they collide (as long as the pair isn't involving the ground plane)
					if (!names.Contains("Ground Plane"))
					{
						_sample.Touched.Add(pair.Shape0.Actor);
						_sample.Touched.Add(pair.Shape1.Actor);
					}
				}
			}
		}
	}
}