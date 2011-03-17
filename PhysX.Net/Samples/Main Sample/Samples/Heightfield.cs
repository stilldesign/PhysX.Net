using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class HeightfieldSample
	{
		public static PhysX.HeightField HeightfieldGrid(Scene scene)
		{
			int rows = 25;
			int columns = 25;

			var samples = new HeightFieldSample[rows * columns];
			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					// Put a z and x curve together
					double h = Math.Sin(c) * Math.Cos(r) * short.MaxValue;

					var sample = new HeightFieldSample()
					{
						Height = (short)h,
						MaterialIndex0 = 0,
						MaterialIndex1 = 1,
						TessellationFlag = 0
					};

					samples[r * columns + c] = sample;
				}
			}

			var heightFieldDesc = new HeightFieldDescription()
			{
				NumberOfRows = rows,
				NumberOfColumns = columns
			};
			heightFieldDesc.SetSamples(samples);

			var heightField = scene.Core.CreateHeightField(heightFieldDesc);

			//

			var heightFieldShapeDesc = new HeightFieldShapeDescription()
			{
				HeightField = heightField,
				HoleMaterial = 2,
				// The max height of our samples is short.MaxValue and we want it to be 1
				HeightScale = 1.0f / (float)short.MaxValue,
				RowScale = 3,
				ColumnScale = 3
			};
			heightFieldShapeDesc.LocalPosition = new Vector3(-0.5f * rows * 1 * heightFieldShapeDesc.RowScale, 0, -0.5f * columns * 1 * heightFieldShapeDesc.ColumnScale);

			var actorDesc = new ActorDescription()
			{
				GlobalPose = Matrix.Translation(100, 0, 0),
				Shapes = { heightFieldShapeDesc }
			};

			var actor = scene.CreateActor(actorDesc);

			return heightField;
		}
	}
}