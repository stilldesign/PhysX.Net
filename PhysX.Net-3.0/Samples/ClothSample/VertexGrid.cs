using System;
using System.Collections.Generic;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.ClothSample
{
	public class VertexGrid
	{
		public VertexGrid(int rows, int columns)
		{
			CreateGrid(rows, columns);
		}

		private void CreateGrid(int rows, int columns)
		{
			int numVertsX = rows + 1;
			int numVertsZ = columns + 1;

			var points = new Vector3[numVertsX * numVertsZ];
			var indices = new int[rows * columns * 2 * 3];

			{
				for (int r = 0; r < numVertsX; r++)
				{
					for (int c = 0; c < numVertsZ; c++)
					{
						points[r * numVertsZ + c] = new Vector3(r, c, 0);
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
}