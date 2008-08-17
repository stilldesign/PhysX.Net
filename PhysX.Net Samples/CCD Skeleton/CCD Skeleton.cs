using System;
using System.Collections.Generic;
using System.IO;

using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Audio;
using Microsoft.Xna.Framework.Content;
using Microsoft.Xna.Framework.GamerServices;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;
using Microsoft.Xna.Framework.Net;
using Microsoft.Xna.Framework.Storage;

using StillDesign.PhysX;


namespace StillDesign
{
	public class Game1 : Microsoft.Xna.Framework.Game
	{
		private Engine _engine;

		private Core _core;
		private Scene _scene;

		public Game1()
		{
			Content.RootDirectory = "Content";

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
		}

		protected override void LoadContent()
		{
			CCDSkeleton ccdSkeletonForBox;

			// Create a CCD Skeleton
			{
				Vector3 size = new Vector3( 5, 5, 5 );

				int[] indices =
                {
                    0,1,3,
                    0,3,2,
                    3,7,6,
                    3,6,2,
                    1,5,7,
                    1,7,3,
                    4,6,7,
                    4,7,5,
                    1,0,4,
                    5,1,4,
                    4,0,2,
                    4,2,6
                };

				Vector3[] vertices =
                {
                    new Vector3(size.X, -size.Y, -size.Z),
                    new Vector3(size.X, -size.Y, size.Z),
                    new Vector3(size.X, size.Y, -size.Z),
                    new Vector3(size.X,  size.Y,  size.Z),
                    new Vector3(-size.X, -size.Y, -size.Z),
                    new Vector3(-size.X, -size.Y, size.Z),
                    new Vector3(-size.X,  size.Y, -size.Z),
                    new Vector3(-size.X,  size.Y,  size.Z)
                };

				TriangleMeshDescription stm = new TriangleMeshDescription();
					stm.AllocateVertices<Vector3>( vertices.Length );
					stm.AllocateTriangles<int>( indices.Length );
					
					stm.VerticesStream.SetData<Vector3>( vertices );
					stm.TriangleStream.SetData<int>( indices );

					stm.VertexCount = vertices.Length;
					stm.TriangleCount = indices.Length / 3;

				ccdSkeletonForBox = _core.CreateCCDSkeleton( stm );

				// Enable CCD and CCD Visualization
				_core.SetParameter( PhysicsParameter.ContinuousCollisionDetection, true );
				_core.SetParameter( PhysicsParameter.VisualizeContinuousCollisionDetectionTests, true );
			}

			// Create a large 2 polygon triangle mesh plane
			// For CCD to work/be used many conditions must be met (check the docs for full list)
			// One of those conditions is that one of the objects must be a triangle mesh or a convex mesh (for static-dynamic)
			{
				Vector3[] vertices = new Vector3[]
				{
					new Vector3( -100, 5, -100 ),
					new Vector3( -100, 5, 100 ),
					new Vector3( 100, 5, -100 ),
					new Vector3( 100, 5, 100 ),
				};

				int[] indices = new int[]
				{
					0, 1, 2,
					1, 3, 2
				};

				TriangleMeshDescription triangleMeshDesc = new TriangleMeshDescription();
					triangleMeshDesc.TriangleCount = indices.Length / 3;
					triangleMeshDesc .VertexCount = vertices.Length;

					triangleMeshDesc.AllocateTriangles<int>( triangleMeshDesc.TriangleCount );
					triangleMeshDesc.AllocateVertices<Vector3>( triangleMeshDesc.VertexCount );

					triangleMeshDesc.TriangleStream.SetData( indices );
					triangleMeshDesc.VerticesStream.SetData( vertices );

				
				MemoryStream s = new MemoryStream();

				Cooking.InitializeCooking();
				Cooking.CookTriangleMesh( triangleMeshDesc, s );
				Cooking.CloseCooking();

				s.Position = 0;
				TriangleMesh triangleMesh = _core.CreateTriangleMesh( s );

				TriangleMeshShapeDescription triangleMeshShapeDesc = new TriangleMeshShapeDescription();
					triangleMeshShapeDesc.TriangleMesh = triangleMesh;
					triangleMeshShapeDesc.Flags = ShapeFlag.Visualization;

				ActorDescription actorDesc = new ActorDescription();
					actorDesc.Shapes.Add( triangleMeshShapeDesc );

				Actor actor = _scene.CreateActor( actorDesc );
			}

			// Make 20 boxes fall down
			for( int x = 0; x < 20; x++ )
			{
				BoxShapeDescription boxShapeDesc = new BoxShapeDescription( 2, 3, 8 );
				// Assign the CCD Skeleton to the shape
				boxShapeDesc.CCDSkeleton = ccdSkeletonForBox;

				ActorDescription actorDesc = new ActorDescription( );
					actorDesc.Name = String.Format( "Box {0}", x );
					actorDesc.BodyDescription = new BodyDescription( 10.0f );
					actorDesc.GlobalPose = Matrix.CreateTranslation( 0, 15 + 3 * x, 0 );
					actorDesc.Shapes.Add( boxShapeDesc );

				Actor actor = _scene.CreateActor( actorDesc );
			}
		}

		protected override void UnloadContent()
		{

		}

		protected override void Update( GameTime gameTime )
		{
			if( GamePad.GetState( PlayerIndex.One ).Buttons.Back == ButtonState.Pressed )
				this.Exit();

			base.Update( gameTime );

			_engine.Update( gameTime );
		}

		protected override void Draw( GameTime gameTime )
		{
			base.Draw( gameTime );

			_engine.Draw();
		}
	}
}
