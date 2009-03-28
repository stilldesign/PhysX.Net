using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Media;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

using StillDesign;
using StillDesign.PhysX;

using ClothVertex = Microsoft.Xna.Framework.Graphics.VertexPositionNormalTexture;

namespace StillDesign
{
	public class Cloth : Microsoft.Xna.Framework.Game
	{
		private Engine _engine;

		private Core _core;
		private Scene _scene;

		private StillDesign.PhysX.Cloth _flag;

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

		private void LoadPhysics()
		{
			// Create a Grid of Points
			VertexGrid grid = VertexGrid.CreateGrid( 10, 10 );

			ClothMeshDescription clothMeshDesc = new ClothMeshDescription();
			clothMeshDesc.AllocateVertices<Vector3>( grid.Points.Length );
			clothMeshDesc.AllocateTriangles<int>( grid.Indices.Length / 3 );

			clothMeshDesc.VertexCount = grid.Points.Length;
			clothMeshDesc.TriangleCount = grid.Indices.Length / 3;

			clothMeshDesc.VerticesStream.SetData( grid.Points );
			clothMeshDesc.TriangleStream.SetData( grid.Indices );

			// We are using 32 bit integers, so make sure the 16 bit flag is removed.
			// 32 bits are the default, so this isn't technically needed
			clothMeshDesc.Flags &= ~MeshFlag.Indices16Bit;

			// Write the cooked data to memory
			MemoryStream memoryStream = new MemoryStream();

			Cooking.InitializeCooking();
			Cooking.CookClothMesh( clothMeshDesc, memoryStream );
			Cooking.CloseCooking();

			// Need to reset the position of the stream to the beginning
			memoryStream.Position = 0;

			ClothMesh clothMesh = _core.CreateClothMesh( memoryStream );

			//

			ClothDescription clothDesc = new ClothDescription()
			{
				ClothMesh = clothMesh,
				Flags = ClothFlag.Gravity | ClothFlag.Bending | ClothFlag.CollisionTwoway | ClothFlag.Visualization,
				GlobalPose =
					Matrix.CreateFromYawPitchRoll( 0, (float)Math.PI / 2.0f, (float)Math.PI / 2.0f ) *
					Matrix.CreateTranslation( 0, 20, 0 )
			};
			clothDesc.MeshData.AllocatePositions<Vector3>( grid.Points.Length );
			clothDesc.MeshData.AllocateIndices<int>( grid.Indices.Length );
			clothDesc.MeshData.AllocateNormals<Vector3>( grid.Points.Length );

			clothDesc.MeshData.MaximumVertices = grid.Points.Length;
			clothDesc.MeshData.MaximumIndices = grid.Indices.Length;

			clothDesc.MeshData.NumberOfVertices = grid.Points.Length;
			clothDesc.MeshData.NumberOfIndices = grid.Indices.Length;

			_flag = _scene.CreateCloth( clothDesc );

			// Flag Pole
			ActorDescription flagPoleActorDesc = new ActorDescription()
			{
				GlobalPose = Matrix.CreateTranslation( 0, 10, 0 ),
				Shapes = { new BoxShapeDescription( 1.0f, 20.0f, 1.0f ) }
			};

			Actor flagPoleActor = _scene.CreateActor( flagPoleActorDesc );

			_flag.AttachToShape( flagPoleActor.Shapes.Single(), 0 );
			_flag.WindAcceleration = new Vector3( 10, 10, 10 );
			_flag.BendingStiffness = 0.1f;
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

			int n = _flag.MeshData.NumberOfVertices.Value;

			var positions = _flag.MeshData.PositionsStream.GetData<Vector3>();
			var normals = _flag.MeshData.NormalsStream.GetData<Vector3>();
			var indicies = _flag.MeshData.IndicesStream.GetData<int>();

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