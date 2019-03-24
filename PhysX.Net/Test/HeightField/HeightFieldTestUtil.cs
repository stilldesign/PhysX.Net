using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Test
{
	public static class HeightFieldTestUtil
	{
		public static HeightFieldSample[] CreateSampleGrid(int rows, int columns, short height = 100)
		{
			var samples = new HeightFieldSample[rows * columns];

			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					// Put a z and x curve together
					double h = System.Math.Sin(c) * System.Math.Cos(r) * height;

					var sample = new HeightFieldSample()
					{
						Height = (short)h
					};

					samples[r * columns + c] = sample;
				}
			}

			return samples;
		}
	}
}