using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace StillDesign.PhysX.Samples
{
	public abstract class Sample
	{
		protected Sample()
		{
			Engine = new Engine();
			Engine.OnUpdate += UpdateEngine;
			Engine.OnDraw += (s, e) => DrawEngine();

			LoadContent();
			LoadPhysics(Engine.Scene);
		}

		private void UpdateEngine(TimeSpan elapsed)
		{
			if (Engine.Keyboard.IsKeyDown(Keys.Escape))
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
			if (Engine.Core != null && !Engine.Core.IsDisposed)
				Engine.Core.Dispose();

			Environment.Exit(0);
		}

		//

		protected Engine Engine { get; private set; }
	}
}