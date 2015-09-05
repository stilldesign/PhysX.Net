using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Input;
using PhysX.Samples.Engine;
using SlimDX;

namespace PhysX.Samples.CharacterSample
{
	public class CharacterSample : Sample
	{
		private CapsuleController _controller;
		private float _rotation;
		private const float _cameraDistance = 15;
		private const float _controllerSpeed = 0.1f;

		public CharacterSample()
		{
			Run();

			_rotation = 0;
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var material = scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var controllerManager = scene.CreateControllerManager();

			// User controllable character
			{
				var desc = new CapsuleControllerDesc()
				{
					Height = 4,
					Radius = 1,
					Material = material,
					UpDirection = new Math.Vector3(0, 1, 0),
					Position = new Math.Vector3(0, 3, 0),
					// TODO: I think this is coming back in 3.3 (> beta 2)
					//Callback = new ControllerHitReport()
				};

				_controller = controllerManager.CreateController<CapsuleController>(desc);
			}

			// Another controller to walk into
			{
				var desc = new CapsuleControllerDesc()
				{
					Height = 4,
					Radius = 1,
					Material = material,
					UpDirection = new Math.Vector3(0, 1, 0),
					Position = new Math.Vector3(15, 3, 15)
				};

				controllerManager.CreateController<CapsuleController>(desc);
			}
		}

		protected override void Update(TimeSpan elapsed)
		{
			// Controllers don't have gravity by default, so we'll need to calculate this acceleration ourselves.
			ProcessGravity();

			//

			// Camera
			Vector3 controllerPosition = _controller.Position.As<Vector3>();

			// Create a rotation matrix around the y-axis
			Matrix rotation = Matrix.RotationAxis(Vector3.UnitY, _rotation);
			// Rotate the 'fowards' vector by the rotation matrix, then stretch it out a distance
			Vector3 cameraOffset = Vector3.TransformCoordinate(-Vector3.UnitZ, rotation) * _cameraDistance;

			// Start at the controllers position, move the camera backwards, move the camera up slightly
			Vector3 p = controllerPosition
				+ cameraOffset
				+ new Vector3(0, 3, 0);

			// Recreate the cameras view matrix from our computed position, target (and static up direction)
			this.Engine.Camera.View = Matrix.LookAtLH(p, controllerPosition, Vector3.UnitY);
		}

		private void ProcessGravity()
		{
			//// Gravity
			//float dt = (float)this.FrameTime.TotalSeconds;

			//if (dt == 0 || dt > 0.5)
			//    return;

			//if (_previousControllerPosition == null)
			//    _previousControllerPosition = _controller.Position;


			//var v = (_controller.Position - _previousControllerPosition.Value) * (1.0f / dt) + this.Scene.Gravity;

			//_previousControllerPosition = _controller.Position;

			//_controller.Move(new PhysX.Math.Vector3(0, (v * dt).Y, 0));

			//Console.WriteLine((v * dt).Y);

			//_controller.ControllerManager.UpdateControllers();
		}

		protected override void ProcessKeyboard(Key[] pressedKeys)
		{
			// Create a rotation matrix around the y-axis
			Matrix rotation = Matrix.RotationAxis(Vector3.UnitY, _rotation);

			// Compute the forwards and right movement vectors
			// The controller will move in its own space, so rotate the usual forwards and right vectors
			Vector3 forward = Vector3.TransformNormal(Vector3.UnitZ, rotation);
			Vector3 right = Vector3.TransformNormal(Vector3.UnitX, rotation);

			Vector3 moveDelta = Vector3.Zero;

			if (pressedKeys.Contains(Key.W))
				moveDelta += forward;
			if (pressedKeys.Contains(Key.S))
				moveDelta += -forward;
			if (pressedKeys.Contains(Key.A))
				moveDelta += -right;
			if (pressedKeys.Contains(Key.D))
				moveDelta += right;

			// Normalize the distance vector (as we may of added two or more components together)
			Vector3 d = Vector3.Normalize(moveDelta);

			// Move the controller in the intended direction * a speed multiplier
			_controller.Move(d.AsPhysX() * _controllerSpeed, this.Engine.FrameTime);
		}
		protected override void ProcessMouse(float deltaX, float deltaY)
		{
			// Add on (either positive or negative) a rotation amount based on the mouse movement
			// This value will be used to create rotation matrices in the above function
			_rotation += deltaX * 0.001f;
		}

		protected override void Draw()
		{

		}
	}
}