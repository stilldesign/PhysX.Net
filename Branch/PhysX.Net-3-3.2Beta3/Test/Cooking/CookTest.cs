using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;
using System.IO;

namespace PhysX.Test
{
	[TestClass]
	public class CookTest : Test
	{
		[TestMethod]
		public void CookClothFabric()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// Create a grid of triangles to be our cloth
				var clothGrid = new VertexGrid(25, 25);

				Cooking cooking = physics.Physics.CreateCooking();

				ClothMeshDesc clothMeshDesc = new ClothMeshDesc()
				{
					Points = clothGrid.Points,
					Triangles = clothGrid.Indices
				};

				var stream = new MemoryStream();

				bool result = cooking.CookClothFabric(clothMeshDesc, new Vector3(0, -9.81f, 0), stream);

				Assert.IsTrue(result);
			}
		}

		[TestMethod]
		public void CookTriangleMesh()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// Create a grid of triangles to be our cloth
				var clothGrid = new VertexGrid(25, 25);

				var cooking = physics.Physics.CreateCooking();

				var desc = new TriangleMeshDesc()
				{
					Points = clothGrid.Points,
					Triangles = clothGrid.Indices
				};

				var stream = new MemoryStream();

				bool result = cooking.CookTriangleMesh(desc, stream);

				Assert.IsTrue(result);
			}
		}

		[TestMethod]
		public void CookConvexMesh()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var vertices = Cuboid.CubeVertices();
				var indices = Cuboid.CubeIndices();

				var cooking = physics.Physics.CreateCooking();

				var desc = new ConvexMeshDesc();
				desc.SetTriangles(indices);
				desc.SetPositions(vertices);
				desc.Flags = ConvexFlag.Indices16Bit | ConvexFlag.ComputeConvex;

				var stream = new MemoryStream();

				bool result = cooking.CookConvexMesh(desc, stream);

				Assert.IsFalse(physics.ErrorOutput.HasErrors, physics.ErrorOutput.LastError);
				Assert.IsTrue(result);
			}
		}

		public class VertexGrid
		{
			public VertexGrid(int rows, int columns)
			{
				CreateGrid(rows, columns);
			}

			private void CreateGrid(int rows, int columns)
			{
				Random rnd = new Random();

				int numVertsX = rows + 1;
				int numVertsZ = columns + 1;

				var points = new Vector3[numVertsX * numVertsZ];
				var indices = new int[rows * columns * 2 * 3];

				{
					for (int r = 0; r < numVertsX; r++)
					{
						for (int c = 0; c < numVertsZ; c++)
						{
							// Make the cloth slightly crumpled (randomize the z position between -0.2 and 0.2)
							float z = -0.2f + (float)rnd.NextDouble() * 0.4f;

							points[r * numVertsZ + c] = new Vector3(r, c, z);
						}
					}
				}

				{
					int count = 0;
					int vi = 0;
					for (int z = 0; z < columns; z++)
					{
						for (int x = 0; x < rows; x++)
						{
							// First triangle
							indices[count++] = vi;
							indices[count++] = vi + 1;
							indices[count++] = vi + numVertsX;

							// Second triangle
							indices[count++] = vi + numVertsX;
							indices[count++] = vi + 1;
							indices[count++] = vi + numVertsX + 1;

							vi++;
						}
						vi++;
					}
				}

				this.Points = points;
				this.Indices = indices;
			}

			public Vector3[] Points { get; private set; }
			public int[] Indices { get; private set; }
		}

		public class Cuboid
		{
			public static Vector3[] CubeVertices()
			{
				// 8 Verticies
				// 12 Edges is 24 Indices

				Vector3 d = new Vector3(0.5f);

				return new[]
				{
					// Back Face
					new Vector3(-d.X, -d.Y, -d.Z), // Left Bottom Back
					new Vector3(-d.X, d.Y, -d.Z), // Left Top Back
					new Vector3(d.X, -d.Y, -d.Z), // Right Bottom Back
					new Vector3(d.X, d.Y, -d.Z), // Right Top Back

					// Front Face
					new Vector3(-d.X, -d.Y, d.Z), // Left Bottom Front
					new Vector3(-d.X, d.Y, d.Z), // Left Top Front
					new Vector3(d.X, -d.Y, d.Z), // Right Bottom Front
					new Vector3(d.X, d.Y, d.Z) // Right Top Front
				};
			}

			public static short[] CubeIndices()
			{
				return new short[]
				{
					// X
					0, 2,
					1, 3,
					4, 6,
					5, 7,

					// Y
					0, 1,
					2, 3,
					4, 5,
					6, 7,

					// Z
					0, 4,
					2, 6,
					1, 5,
					3, 7
				};
			}
		}
	}
}