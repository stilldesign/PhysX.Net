using System;
using System.Drawing;
using System.Windows.Input;
using SlimDX;
using SlimDX.Direct3D10;
using System.Runtime.InteropServices;

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
			this.Projection = Matrix.PerspectiveFovLH((float)(Math.PI / 4.0), Viewport.AspectRatio(), 0.5f, 10000);

			CenterCursor();
		}

		public void Update(TimeSpan elapsedTime)
		{
			var mousePos = Mouse.GetPosition(null) - new System.Windows.Point(_engine.Window.Left, _engine.Window.Top);
			SetCursorPos((int)mousePos.X, (int)mousePos.Y);

			Vector2 cursorPosition = new Vector2((float)mousePos.X, (float)mousePos.Y);
			Vector2 mouseCenter = new Vector2((int)_engine.Window.Width / 2, (int)_engine.Window.Height / 2);
			Vector2 delta = cursorPosition - mouseCenter;
			Vector2 deltaDampened = delta * 0.0005f;
			CenterCursor();

			// Should perhaps extract the yaw and pitch from the current direction of the camera
			_cameraYaw += deltaDampened.X;
			_cameraPitch += deltaDampened.Y;

			//

			Vector3 forward = Mathematics.DirectionFromViewMatrix(Matrix.Invert(this.View));
			Vector3 position = Mathematics.DecomposeToPosition(Matrix.Invert(this.View));

			Matrix cameraRotation = Matrix.RotationYawPitchRoll(_cameraYaw, _cameraPitch, 0);
			Vector3 newForward = Vector3.TransformNormal(Vector3.UnitZ, cameraRotation);

			double elapsed = elapsedTime.TotalSeconds; // Elapsed time since last frame in seconds
			const double speed = 20.0; // 20 distance units per second
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

		//

		[DllImport("user32.dll")]
		static extern bool SetCursorPos(int X, int Y);
		//[DllImport("user32.dll")]
		//[return: MarshalAs(UnmanagedType.Bool)]
		//static extern bool GetCursorPos(out MS.Win32.POINT lpPoint);
	}
}