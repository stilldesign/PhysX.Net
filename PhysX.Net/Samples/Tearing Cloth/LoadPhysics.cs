using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	partial class TearingCloth
	{
		protected override void LoadPhysics(Scene scene)
		{
			int w = 25;
			int h = 25;

			float hw = w / 2.0f;
			float hh = h / 2.0f;

			Vector3 p = new Vector3(0, 20, 0);

			// Create a Grid of Points
			int vertices, indices;

			ClothMesh clothMesh;
			{
				VertexGrid grid = VertexGrid.CreateGrid(w, h);

				vertices = grid.Points.Length;
				indices = grid.Indices.Length;

				ClothMeshDescription clothMeshDesc = new ClothMeshDescription();
				clothMeshDesc.AllocateVertices<Vector3>(vertices);
				clothMeshDesc.AllocateTriangles<int>(indices / 3);

				clothMeshDesc.VertexCount = vertices;
				clothMeshDesc.TriangleCount = indices / 3;

				clothMeshDesc.VerticesStream.SetData(grid.Points);
				clothMeshDesc.TriangleStream.SetData(grid.Indices);

				// We are using 32 bit integers, so make sure the 16 bit flag is removed.
				// 32 bits are the default, so this isn't technically needed
				clothMeshDesc.Flags &= ~MeshFlag.Indices16Bit;
				clothMeshDesc.Flags = (MeshFlag)((int)clothMeshDesc.Flags | (int)ClothMeshFlag.Tearable);

				// Write the cooked data to memory
				using (var memoryStream = new MemoryStream())
				{
					Cooking.InitializeCooking();
					Cooking.CookClothMesh(clothMeshDesc, memoryStream);
					Cooking.CloseCooking();

					// Need to reset the position of the stream to the beginning
					memoryStream.Position = 0;

					clothMesh = Engine.Core.CreateClothMesh(memoryStream);
				}
			}

			//

			int j = vertices * 2;
			int k = indices * 3;

			var clothDesc = new ClothDescription()
			{
				ClothMesh = clothMesh,
				GlobalPose =
					Matrix.Translation(-hw, 0, -hh) *
					Matrix.Translation(p),
				Flags = ClothFlag.Gravity | ClothFlag.Bending | ClothFlag.CollisionTwoway | ClothFlag.Visualization | ClothFlag.Tearable,
				BendingStiffness = 0.1f,
				TearFactor = 1.5f
			};
			clothDesc.MeshData.AllocatePositions<Vector3>(j);
			clothDesc.MeshData.AllocateIndices<int>(k);
			clothDesc.MeshData.AllocateNormals<Vector3>(j);

			clothDesc.MeshData.MaximumVertices = j;
			clothDesc.MeshData.MaximumIndices = k;

			clothDesc.MeshData.NumberOfVertices = vertices;
			clothDesc.MeshData.NumberOfIndices = indices;

			_cloth = scene.CreateCloth(clothDesc);

			//

			// Four corner boxes to hold it in place
			var positions = new[]
			{
				new Vector3(0, 0, -hh), // Back
				new Vector3(0, 0, hh), // Front
				new Vector3(-hw, 0, 0), // Left
				new Vector3(hw, 0, 0), // Right
			};

			var sizes = new[]
			{
				new Vector3(w, 1, 1), // Back
				new Vector3(w, 1, 1), // Front
				new Vector3(1, 1, h), // Left
				new Vector3(1, 1, h), //Right
			};

			for (int i = 0; i < 4; i++)
			{
				var actorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.Translation(positions[i] + p),
					Shapes = { new BoxShapeDescription(sizes[i]) }
				};

				var actor = scene.CreateActor(actorDesc);

				_cloth.AttachToShape(actor.Shapes.First(), (ClothAttachmentFlag)0);
			}

			//

			// Something to drop on it
			{
				var actorDesc = new ActorDescription()
				{
					GlobalPose = Matrix.Translation(0, 100, 0),
					Shapes = { new SphereShapeDescription(2) },
					BodyDescription = new BodyDescription(50)
				};

				var actor = scene.CreateActor(actorDesc);
			}
		}

		private void CreateBox()
		{
			var random = new Random();

			int w = random.Next(1, 8);
			int h = random.Next(1, 8);
			int d = random.Next(1, 8);

			int x = random.Next(-10, 10);
			int y = random.Next(-10, 10);

			var desc = new ActorDescription(new BoxShapeDescription(w, h, d))
			{
				BodyDescription = new BodyDescription(100),
				GlobalPose =
					Matrix.RotationY((float)(random.NextDouble() * 2 * Math.PI)) *
					Matrix.Translation(x, 50, y)
			};

			var actor = Engine.Scene.CreateActor(desc);
		}
	}
}