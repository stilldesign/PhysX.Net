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

			Update(elapsed);
		}
		protected void DrawEngine()
		{
			Draw();
		}

		protected abstract void LoadContent();
		protected abstract void LoadPhysics(Scene scene);
		protected abstract void Update(TimeSpan elapsed);
		protected abstract void Draw();

		protected void Run()
		{
			Engine.Run();
		}
		protected void Shutdown()
		{
			if (Engine.Core != null && !Engine.Core.Disposed)
				Engine.Core.Dispose();

			Environment.Exit(0);
		}

		//

		protected PhysX.Samples.Engine.Engine Engine { get; private set; }
	}
}