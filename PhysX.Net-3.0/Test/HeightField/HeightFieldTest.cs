using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class HeightFieldTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeHeightField()
		{
			using (CreatePhysicsAndScene())
			{
				const int rows = 25, columns = 25;
				var samples = CreateSampleGrid(rows, columns);

				var heightFieldDesc = new HeightFieldDesc()
				{
					NumberOfRows = rows,
					NumberOfColumns = columns,
					Samples = samples
				};

				HeightField heightField;
				using (heightField = Physics.CreateHeightField(heightFieldDesc))
				{
					Assert.IsNotNull(heightField);
					Assert.IsFalse(heightField.Disposed);
				}

				Assert.IsTrue(heightField.Disposed);
			}
		}

		private static HeightFieldSample[] CreateSampleGrid(int rows, int columns)
		{
			var samples = new HeightFieldSample[rows * columns];

			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					// Put a z and x curve together
					double h = System.Math.Sin(c) * System.Math.Cos(r) * short.MaxValue;

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