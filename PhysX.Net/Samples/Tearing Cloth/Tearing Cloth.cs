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
	public class TearingCloth : Microsoft.Xna.Framework.Game
	{
		private Engine _engine;

		private Core _core;
		private Scene _scene;

		private Cloth _cloth;

		private BasicEffect _lighting;

		public TearingCloth()
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
			int w = 15;
			int h = 15;

			Vector3 p = new Vector3( 0, 20, 0 );

			// Create a Grid of Points
			int vertices, indices;

			ClothMesh clothMesh;
			{
				VertexGrid grid = VertexGrid.CreateGrid( w, h );

				vertices = grid.Points.Length;
				indices = grid.Indices.Length;

				ClothMeshDescription clothMeshDesc = new ClothMeshDescription();
					clothMeshDesc.AllocateVertices<Vector3>( vertices );
					clothMeshDesc.AllocateTriangles<int>( indices / 3 );

					clothMeshDesc.VertexCount = vertices;
					clothMeshDesc.TriangleCount = indices / 3;

					clothMeshDesc.VerticesStream.SetData( grid.Points );
					clothMeshDesc.TriangleStream.SetData( grid.Indices );

					// We are using 32 bit integers, so make sure the 16 bit flag is removed.
					// 32 bits are the default, so this isn't technically needed
					clothMeshDesc.Flags &= ~MeshFlag.Indices16Bit;
					clothMeshDesc.Flags = (MeshFlag)( (int)clothMeshDesc.Flags | (int)ClothMeshFlag.Tearable );

				// Write the cooked data to memory
				MemoryStream memoryStream = new MemoryStream();

				Cooking.InitializeCooking();
				Cooking.CookClothMesh( clothMeshDesc, memoryStream );
				Cooking.CloseCooking();

				// Need to reset the position of the stream to the beginning
				memoryStream.Position = 0;

				clothMesh = _core.CreateClothMesh( memoryStream );
			}

			//

			int v = vertices * 2;
			int i = indices * 3;

			ClothDescription clothDesc = new ClothDescription()
			{
				ClothMesh = clothMesh,
				GlobalPose =
					Matrix.CreateTranslation( -w / 2.0f, 0, -h / 2.0f ) *
					Matrix.CreateTranslation( p ),
				Flags = ClothFlag.Gravity | ClothFlag.Bending | ClothFlag.CollisionTwoway | ClothFlag.Visualization | ClothFlag.Tearable,
				BendingStiffness = 0.1f
			};
			clothDesc.MeshData.AllocatePositions<Vector3>( v );
			clothDesc.MeshData.AllocateIndices<int>( i );
			clothDesc.MeshData.AllocateNormals<Vector3>( v );

			clothDesc.MeshData.MaximumVertices = v;
			clothDesc.MeshData.MaximumIndices = i;

			clothDesc.MeshData.NumberOfVertices = vertices;
			clothDesc.MeshData.NumberOfIndices = indices;

			_cloth = _scene.CreateCloth( clothDesc );

			//

			// Four corner boxes to hold it in place
			var positions = new[]
				{
					new Vector3( -w/2.0f, 0, -h/2.0f ), // Left back
					new Vector3( -w/2.0f, 0, h/2.0f ), // Left front
					new Vector3( w/2.0f, 0, -h/2.0f ), // Right back
					new Vector3( w/2.0f, 0, h/2.0f ), // Right front
				};

			for( int x = 0; x < 4; x++ )
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.CreateTranslation( positions[ x ] + p ),
					Shapes = { new BoxShapeDescription( 1.0f, 1.0f, 1.0f ) }
				};

				Actor actor = _scene.CreateActor( actorDesc );

				_cloth.AttachToShape( actor.Shapes.Single(), 0 );
			}

			//

			// Something to drop on it
			{
				ActorDescription actorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.CreateTranslation( 0, 100, 0 ),
					Shapes = { new SphereShapeDescription( 2.0f ) },
					BodyDescription = new BodyDescription( 50.0f )
				};

				Actor actor = _scene.CreateActor( actorDesc );
			}
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

				default:
					throw new Exception();
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