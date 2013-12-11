using System;
using System.Runtime.InteropServices;
using System.Windows.Input;
using SlimDX;
using SlimDX.Direct3D10;
using System.Drawing;

namespace PhysX.Samples.Engine
{
	public class Camera
	{
		private Engine _engine;
		private float _cameraPitch, _cameraYaw;

		internal Camera(Engine engine)
		{
			_engine = engine;

			this.Viewport = new Viewport(0, 0, (int)_engine.Window.Width, (int)_engine.Window.Height);
			this.View = Matrix.LookAtLH(new Vector3(0, 20, -90), new Vector3(0, 20, 0), new Vector3(0, 1, 0));
			this.Projection = Matrix.PerspectiveFovLH((float)(System.Math.PI / 4.0), Viewport.AspectRatio(), 0.5f, 10000);

			CenterCursor();
		}

		public void Update(TimeSpan elapsedTime)
		{
			Vector2 delta = GetMouseDelta();
			Vector2 deltaDampened = delta * 0.0005f;
			CenterCursor();

			this.MouseDelta = delta;

			// Should perhaps extract the yaw and pitch from the current direction of the camera
			_cameraYaw += deltaDampened.X;
			_cameraPitch += deltaDampened.Y;

			//

			Vector3 forward = Mathematics.DirectionFromViewMatrix(Matrix.Invert(this.View));
			Vector3 position = Mathematics.DecomposeToPosition(Matrix.Invert(this.View));

			Matrix cameraRotation = Matrix.RotationYawPitchRoll(_cameraYaw, _cameraPitch, 0);
			Vector3 newForward = Vector3.TransformNormal(Vector3.UnitZ, cameraRotation);

			double elapsed = elapsedTime.TotalSeconds; // Elapsed time since last frame in seconds
			double speedMultiplier = (_engine.Keyboard.IsKeyDown(Key.LeftShift) ? 2 : 1);
			double speed = 40.0 * speedMultiplier; // 40 distance units per second
			float distance = (float)(speed * elapsed); // d = vt

			// The amount of movement * the direction of movement, then rotate that along the direction we are looking
			Vector3 translateDirection = Vector3.Zero;

			if (_engine.Keyboard.IsKeyDown(Key.W)) // Forwards
				translateDirection += Vector3.TransformNormal(Vector3.UnitZ, cameraRotation);

			if (_engine.Keyboard.IsKeyDown(Key.S)) // Backwards
				translateDirection += Vector3.TransformNormal(-Vector3.UnitZ, cameraRotation);

			if (_engine.Keyboard.IsKeyDown(Key.A)) // Left
				translateDirection += Vector3.TransformNormal(-Vector3.UnitX, cameraRotation);

			if (_engine.Keyboard.IsKeyDown(Key.D)) // Right
				translateDirection += Vector3.TransformNormal(Vector3.UnitX, cameraRotation);

			Vector3 newPosition = position;

			if (translateDirection.LengthSquared() > 0)
				newPosition += Vector3.Normalize(translateDirection) * distance;

			this.View = Matrix.LookAtLH(newPosition, newPosition + newForward, Vector3.UnitY);
		}

		private Vector2 GetMouseDelta()
		{
			Point p;
			GetCursorPos(out p);

			var mousePos = p - new Size((int)_engine.Window.Left, (int)_engine.Window.Top);

			Vector2 cursorPosition = new Vector2(mousePos.X, mousePos.Y);
			Vector2 mouseCenter = new Vector2((float)_engine.Window.Width / 2, (float)_engine.Window.Height / 2);

			return cursorPosition - mouseCenter;
		}

		private void CenterCursor()
		{
			Point l = new Point((int)_engine.Window.Left, (int)_engine.Window.Top);
			Size s = new Size((int)_engine.Window.Width, (int)_engine.Window.Height);

			SetCursorPos(l.X + s.Width / 2, l.Y + s.Height / 2);
		}

		//

		public Matrix View { get; set; }
		public Matrix Projection { get; private set; }

		public Viewport Viewport { get; set; }

		public Vector3 Position
		{
			get
			{
				Matrix viewI = Matrix.Invert(this.View);

				return new Vector3(viewI.M41, viewI.M42, viewI.M43);
			}
		}
		public Vector3 Direction
		{
			get
			{
				return Vector3.Normalize(new Vector3(View.M13, View.M23, View.M33));
			}
		}

		/// <summary>
		/// Gets the change in mouse position (in pixels).
		/// This value is updated each frame.
		/// </summary>
		public Vector2 MouseDelta { get; private set; }

		//

		[DllImport("user32.dll")]
		static extern bool SetCursorPos(int X, int Y);
		[DllImport("user32.dll")]
		public static extern bool GetCursorPos(out System.Drawing.Point pt);
	}
}