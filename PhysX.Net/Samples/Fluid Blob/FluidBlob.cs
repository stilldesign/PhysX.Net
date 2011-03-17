using System;
using System.Collections.Generic;
using System.Linq;
using SlimDX;

namespace StillDesign.PhysX.Samples
{
	public partial class FluidBlob : Sample
	{
		public FluidBlob()
		{
			Engine.Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void Update(TimeSpan elapsed)
		{
			var p = this.Engine.Scene.Fluids[0].ParticleWriteData.PositionBuffer.GetData<Vector3>();

			if (!p.Any())
				return;

			// Displays particle 0 (which may not be the same particle each simulation step) position in the window title
			// Getting the entire set of particle positions each frame is not the best way, but its just for demo (use PositionBuffer.Position and PositionBuffer.Read instead)
			Vector3 position = p.First();

			//this.Window.Title = String.Format("Particle 0 is positioned at: {0:0.00}, {1:0.00}, {2:0.00}", position.X, position.Y, position.Z);
		}

		protected override void Draw()
		{

		}
	}
}