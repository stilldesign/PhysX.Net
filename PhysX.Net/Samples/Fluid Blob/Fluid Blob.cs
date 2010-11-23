using System;
using System.Collections.Generic;
using System.Linq;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace StillDesign.PhysX.Samples
{
	public partial class FluidBlob : Microsoft.Xna.Framework.Game
	{
		public FluidBlob()
		{
			this.Engine = new Engine( this );
		}

		protected override void Initialize()
		{
			this.Engine.Initalize();

			base.Initialize();
		}

		protected override void LoadContent()
		{
			LoadPhysics();

			base.LoadContent();
		}

		protected override void UnloadContent()
		{

		}

		protected override void Update( GameTime gameTime )
		{
			HandleKeyboard( Keyboard.GetState() );

			this.Engine.Update( gameTime );

			// Displays particle 0 (which may not be the same particle each simulation step) position in the window title
			// Getting the entire set of particle positions each frame is not the best way, but its just for demo (use PositionBuffer.Position and PositionBuffer.Read instead)
			Vector3 position = this.Engine.Scene.Fluids[ 0 ].ParticleWriteData.PositionBuffer.GetData<Vector3>().First();
			this.Window.Title = String.Format( "Particle 0 is positioned at: {0:0.00}, {1:0.00}, {2:0.00}", position.X, position.Y, position.Z );

			base.Update( gameTime );
		}

		protected override void Draw( GameTime gameTime )
		{
			this.Engine.Draw();

			base.Draw( gameTime );
		}

		private void HandleKeyboard( KeyboardState keyboardState )
		{
			if( keyboardState.IsKeyDown( Keys.Escape ) )
				this.Exit();
		}

		private Engine Engine
		{
			get;
			set;
		}
	}
}