using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace StillDesign.PhysX.Samples
{
	public partial class TearingCloth : Microsoft.Xna.Framework.Game
	{
		private Engine _engine;

		private Core _core;
		private Scene _scene;

		private Cloth _cloth;

		private BasicEffect _lighting;

		private DateTime _keyboardDelay;

		public TearingCloth()
		{
			_engine = new Engine( this );

			_keyboardDelay = DateTime.MinValue;
		}

		protected override void Initialize()
		{
			_engine.Initalize();

			// For convenience
			_core = _engine.Core;
			_scene = _engine.Scene;

			// Initalize the content
			base.Initialize();

			LoadPhysics();
		}

		protected override void LoadContent()
		{
			_lighting = new BasicEffect( _engine.Device, null );

			_engine.Camera.View = Matrix.CreateLookAt( new Vector3( 0, 20, 30 ), new Vector3( 0, 20, 0 ), new Vector3( 0, 1, 0 ) );
		}
		protected override void UnloadContent()
		{

		}

		protected override void Update( GameTime gameTime )
		{
			HandleKeyboard( Keyboard.GetState() );

			_engine.Update( gameTime );

			base.Update( gameTime );
		}

		protected override void Draw( GameTime gameTime )
		{
			base.Draw( gameTime );

			_engine.Draw();

			//int n = _cloth.MeshData.NumberOfVertices.Value;

			//var positions = _cloth.MeshData.PositionsStream.GetData<Vector3>();
			//var normals = _cloth.MeshData.NormalsStream.GetData<Vector3>();
			//var indicies = _cloth.MeshData.IndicesStream.GetData<int>();

			//ClothVertex[] vertices = new ClothVertex[ n ];

			//for( int x = 0; x < n; x++ )
			//{
			//    vertices[ x ].Position = positions[ x ];
			//    vertices[ x ].Normal = normals[ x ];
			//}

			//_lighting.TextureEnabled = false;
			//_lighting.World = Matrix.Identity;
			//_lighting.View = _engine.Camera.View;
			//_lighting.Projection = _engine.Camera.Projection;
			//_lighting.LightingEnabled = false;

			//_lighting.Begin();
			//foreach( var pass in _lighting.CurrentTechnique.Passes )
			//{
			//    pass.Begin();
			//    _engine.Device.DrawUserIndexedPrimitives<ClothVertex>( PrimitiveType.TriangleList, vertices, 0, n, indicies, 0, indicies.Length / 3 );
			//    pass.End();
			//}
			//_lighting.End();
		}

		private void HandleKeyboard( KeyboardState keyboardState )
		{
			if( keyboardState.IsKeyDown( Keys.Escape ) )
				this.Exit();

			if( keyboardState.IsKeyDown( Keys.Space ) )
			{
				if( DateTime.Now - _keyboardDelay > TimeSpan.FromMilliseconds( 100 ) )
				{
					CreateBox();

					_keyboardDelay = DateTime.Now;
				}
			}
		}
	}
}