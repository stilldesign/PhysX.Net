using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using SlimDX.Direct3D10;
using SlimDX.DXGI;
using StillDesign.PhysX;

using Matrix = StillDesign.PhysX.MathPrimitives.Matrix;
using Vector3 = StillDesign.PhysX.MathPrimitives.Vector3;

namespace StillDesign.PhysX.Samples
{
	public delegate void ContactCallback(Actor a, Actor b, ContactPairFlag events);

	public partial class MainSample : Sample
	{
		private VehicleSample _basicVehicle;
		private Model _torusModel;

		//

		public MainSample()
		{
			Run();
		}

		protected override void LoadContent()
		{
			
		}

		/// <summary>Simple examples of all the PhysX bits running together.</summary>
		protected override void LoadPhysics(Scene scene)
		{
			// The ground plane (if created) sould be the first actor
			var groundActor = scene.Actors.First();
			groundActor.Name = "Default Ground Plane";

			//

			// Create most of the PhysX objects available
			RigidBodySample.SimpleBoxes(scene);
			ClothSample.FlagOfCloth(scene);
			JointSample.RevoluteJoint(scene);
			JointSample.PrismaticJointWithLimit(scene);
			FluidSample.FluidWithEmitterAndDrain(scene);
			ForceFieldSample.CreateForceField(scene);
			HeightfieldSample.HeightfieldGrid(scene);
			_torusModel = ConvexSample.ActorWithConvexShape(scene, Engine.GraphicsDevice);
			ControllerSample.CapsuleController(scene);

			// Enable to view soft bodies, they run slowly
			if (false)
				SoftBodySample.TeapotSoftBody(scene);

			_basicVehicle = new VehicleSample(Engine.Scene);
		}

		protected override void Update(TimeSpan elapsed)
		{
			// Drive the vehicle
			if (Engine.Keyboard.IsKeyDown(Keys.Up))
				_basicVehicle.Accelerate(3);

			// Steering (Positive is a counter-clockwise turn)
			if (Engine.Keyboard.IsKeyDown(Keys.Left))
				_basicVehicle.Turn(0.05f);
			if (Engine.Keyboard.IsKeyDown(Keys.Right))
				_basicVehicle.Turn(-0.05f);
		}

		protected override void Draw()
		{
			Engine.DrawSimple(_torusModel.VertexBuffer, _torusModel.IndexBuffer, _torusModel.IndexCount);
		}

		//

		public Actor GroundActor { get; private set; }
	}
}