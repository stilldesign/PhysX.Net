using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;
using System.IO;

namespace StillDesign.PhysX.Samples
{
	partial class TearingCloth
	{
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
				using( MemoryStream memoryStream = new MemoryStream() )
				{
					Cooking.InitializeCooking();
					Cooking.CookClothMesh( clothMeshDesc, memoryStream );
					Cooking.CloseCooking();

					// Need to reset the position of the stream to the beginning
					memoryStream.Position = 0;

					clothMesh = _core.CreateClothMesh( memoryStream );
				}
			}

			//

			int v = vertices * 2;
			int i = indices * 3;

			ClothDescription clothDesc = new ClothDescription()
			{
				ClothMesh = clothMesh,
				GlobalPose =
					Matrix.Translation( -w / 2.0f, 0, -h / 2.0f ) *
					Matrix.Translation( p ),
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
					GlobalPose = Matrix.Translation( positions[ x ] + p ),
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
					GlobalPose = Matrix.Translation( 0, 100, 0 ),
					Shapes = { new SphereShapeDescription( 2.0f ) },
					BodyDescription = new BodyDescription( 50.0f )
				};

				Actor actor = _scene.CreateActor( actorDesc );
			}
		}

		private void CreateBox()
		{
			Random random = new Random();

			ActorDescription desc = new ActorDescription( new BoxShapeDescription( 20, 1, 1 ) )
			{
				BodyDescription = new BodyDescription( 10 ),
				GlobalPose =
					Matrix.RotationY( (float)( random.NextDouble() * 2 * Math.PI ) ) *
					Matrix.Translation( 0, 50, 0 )
			};

			Actor actor = _scene.CreateActor( desc );
		}
	}
}