using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Input;

namespace PhysX.Samples
{
	public abstract class Sample
	{
		protected Sample()
		{
			Engine = new PhysX.Samples.Engine.Engine();
			Engine.OnUpdate += UpdateEngine;
			Engine.OnDraw += (s, e) => DrawEngine();

			LoadContent();
			LoadPhysics(Engine.Scene);
		}

		private void UpdateEngine(TimeSpan elapsed)
		{
			if (Engine.Keyboard.IsKeyDown(Key.Escape))
			{
				Shutdown();
				return;
			}

			UpdateSample(elapsed);
		}
		protected void DrawEngine()
		{
			Draw();
		}

		protected abstract void LoadContent();
		protected abstract void LoadPhysics(Scene scene);
		private void UpdateSample(TimeSpan elapsed)
		{
			ProcessKeyboard(Engine.Keyboard.PressedKeys.ToArray());

			ProcessMouse(Engine.Camera.MouseDelta.X, Engine.Camera.MouseDelta.Y);

			Update(elapsed);
		}
		protected abstract void Update(TimeSpan elapsed);
		protected abstract void Draw();
		protected virtual void ProcessKeyboard(Key[] pressedKeys)
		{

		}
		protected virtual void ProcessMouse(float deltaX, float deltaY)
		{

		}

		protected void Run()
		{
			Engine.Run();
		}
		protected void Shutdown()
		{
			if (Engine.Physics != null && !Engine.Physics.Disposed)
				Engine.Physics.Dispose();

			Environment.Exit(0);
		}

		//

		protected PhysX.Samples.Engine.Engine Engine { get; private set; }

		public TimeSpan FrameTime
		{
			get
			{
				return Engine.FrameTime;
			}
		}

		public Scene Scene
		{
			get
			{
				return Engine.Scene;
			}
		}
	}
}