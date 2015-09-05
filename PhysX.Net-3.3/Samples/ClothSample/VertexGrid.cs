using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

namespace PhysX.Samples.ClothSample
{
	public class VertexGrid
	{
		private VertexGrid()
		{

		}

		public static VertexGrid CreateGrid(int rows, int columns, float particleSpacing = 1.0f)
		{
			var rnd = new Random();

			int numVertsX = rows + 1;
			int numVertsZ = columns + 1;

			var points = new Vector3[numVertsX * numVertsZ];
			var indices = new int[rows * columns * 2 * 3];

			{
				for (int r = 0; r < numVertsX; r++)
				{
					for (int c = 0; c < numVertsZ; c++)
					{
						float x = r * particleSpacing;
						float y = c * particleSpacing;
						// Make the cloth slightly crumpled (randomize the z position between -0.2 and 0.2)
						float z = -0.2f + (float)rnd.NextDouble() * 0.4f;

						points[r * numVertsZ + c] = new Vector3(x, y, z);
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

			return new VertexGrid()
			{
				Points = points,
				Indices = indices
			};
		}

		public Vector3[] Points { get; private set; }
		public int[] Indices { get; private set; }
	}
}