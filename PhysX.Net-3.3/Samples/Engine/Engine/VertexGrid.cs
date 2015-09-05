using System;
using System.Collections.Generic;
using System.Linq;
using SharpDX;

namespace PhysX.Samples
{
	public class VertexGrid
	{
		private VertexGrid(Vector3[] points, int[] indices)
		{
			this.Points = points;
			this.Indices = indices;
		}

		public static VertexGrid CreateGrid(int rows, int columns)
		{
			int numVertsX = rows + 1;
			int numVertsZ = columns + 1;

			VertexGrid grid = new VertexGrid(new Vector3[numVertsX * numVertsZ], new int[rows * columns * 2 * 3]);

			{
				for (int r = 0; r < numVertsX; r++)
				{
					for (int c = 0; c < numVertsZ; c++)
					{
						grid.Points[r * numVertsZ + c] = new Vector3(r, 0, c);
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
						grid.Indices[count++] = vi;
						grid.Indices[count++] = vi + 1;
						grid.Indices[count++] = vi + numVertsX;

						// Second triangle
						grid.Indices[count++] = vi + numVertsX;
						grid.Indices[count++] = vi + 1;
						grid.Indices[count++] = vi + numVertsX + 1;

						vi++;
					}
					vi++;
				}
			}

			return grid;
		}

		public Vector3[] Points { get; private set; }
		public int[] Indices { get; private set; }
	}
}