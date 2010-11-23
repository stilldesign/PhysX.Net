using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;
using System.IO;

namespace StillDesign.PhysX.Samples
{
	partial class Cloth
	{
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
			ClothMesh clothMesh;

			using( MemoryStream memoryStream = new MemoryStream() )
			{
				Cooking.InitializeCooking();
				Cooking.CookClothMesh( clothMeshDesc, memoryStream );
				Cooking.CloseCooking();

				// Need to reset the position of the stream to the beginning
				memoryStream.Position = 0;

				clothMesh = _core.CreateClothMesh( memoryStream );
			}

			//

			ClothDescription clothDesc = new ClothDescription()
			{
				ClothMesh = clothMesh,
				Flags = ClothFlag.Gravity | ClothFlag.Bending | ClothFlag.CollisionTwoway | ClothFlag.Visualization,
				GlobalPose =
					Matrix.RotationYawPitchRoll( 0, (float)Math.PI / 2.0f, (float)Math.PI / 2.0f ) *
					Matrix.Translation( 0, 20, 0 )
			};
			clothDesc.MeshData.AllocatePositions<Vector3>( grid.Points.Length );
			clothDesc.MeshData.AllocateIndices<int>( grid.Indices.Length );
			clothDesc.MeshData.AllocateNormals<Vector3>( grid.Points.Length );

			clothDesc.MeshData.MaximumVertices = grid.Points.Length;
			clothDesc.MeshData.MaximumIndices = grid.Indices.Length;

			clothDesc.MeshData.NumberOfVertices = grid.Points.Length;
			clothDesc.MeshData.NumberOfIndices = grid.Indices.Length;

			_flag = _scene.CreateCloth( clothDesc );
			_flagMeshData = _flag.GetMeshData();

			// Flag Pole
			ActorDescription flagPoleActorDesc = new ActorDescription()
			{
				GlobalPose = Matrix.Translation( 0, 10, 0 ),
				Shapes = { new BoxShapeDescription( 1.0f, 20.0f, 1.0f ) }
			};

			Actor flagPoleActor = _scene.CreateActor( flagPoleActorDesc );

			_flag.AttachToShape( flagPoleActor.Shapes.Single(), 0 );
			_flag.WindAcceleration = new Vector3( 10, 10, 10 );
			_flag.BendingStiffness = 0.1f;

			_core.Parameters.VisualizeClothMesh = true;
		}
	}
}