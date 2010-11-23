using System;
using System.Linq;
using System.Collections.Generic;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

using ClothVertex = Microsoft.Xna.Framework.Graphics.VertexPositionNormalTexture;

namespace StillDesign.PhysX.Samples
{
	public partial class Cloth : Microsoft.Xna.Framework.Game
	{
		private Engine _engine;

		private Core _core;
		private Scene _scene;

		private StillDesign.PhysX.Cloth _flag;
		private MeshData _flagMeshData;

		private BasicEffect _lighting;

		public Cloth()
		{
			_engine = new Engine( this );
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

			_engine.Device.RenderState.CullMode = CullMode.CullClockwiseFace;

			UpdateWindowTitle();
		}

		protected override void LoadContent()
		{
			_lighting = new BasicEffect( _engine.Device, null );
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

			int n = _flagMeshData.NumberOfVertices.Value;

			var positions = _flagMeshData.PositionsStream.GetData<Vector3>();
			var normals = _flagMeshData.NormalsStream.GetData<Vector3>();
			var indicies = _flagMeshData.IndicesStream.GetData<int>();

			ClothVertex[] vertices = new ClothVertex[ n ];

			for( int x = 0; x < n; x++ )
			{
				vertices[ x ].Position = positions[ x ];
				vertices[ x ].Normal = normals[ x ];
			}

			_lighting.TextureEnabled = false;
			_lighting.World = Matrix.Identity;
			_lighting.View = _engine.Camera.View;
			_lighting.Projection = _engine.Camera.Projection;
			_lighting.LightingEnabled = false;

			_engine.Device.VertexDeclaration = new VertexDeclaration( _engine.Device, ClothVertex.VertexElements );

			_lighting.Begin();
				foreach( var pass in _lighting.CurrentTechnique.Passes )
				{
					pass.Begin();
						_engine.Device.DrawUserIndexedPrimitives<ClothVertex>( PrimitiveType.TriangleList, vertices, 0, n, indicies, 0, indicies.Length / 3 );
					pass.End();
				}
			_lighting.End();
		}

		private void HandleKeyboard( KeyboardState keyboardState )
		{
			if( keyboardState.IsKeyDown( Keys.Escape ) )
				this.Exit();
			
			if( keyboardState.IsKeyDown( Keys.C ) )
				CycleCullMode();
		}

		private void CycleCullMode()
		{
			switch( _engine.Device.RenderState.CullMode )
			{
				case CullMode.CullClockwiseFace:
					_engine.Device.RenderState.CullMode = CullMode.CullCounterClockwiseFace;
				break;
				case CullMode.CullCounterClockwiseFace:
					_engine.Device.RenderState.CullMode = CullMode.None;
				break;
				case CullMode.None:
					_engine.Device.RenderState.CullMode = CullMode.CullClockwiseFace;
				break;

				default: throw new Exception();
			}

			UpdateWindowTitle();

			//HACK: Easy way of getting round the face that XNA doesn't support key up events
			System.Threading.Thread.Sleep( 200 );
		}

		private void UpdateWindowTitle()
		{
			_engine.Game.Window.Title = String.Format( "StillDesign.PhysX.Net - Cloth Sample - (C)ull Mode: {0}", _engine.Device.RenderState.CullMode );
		}
	}
}