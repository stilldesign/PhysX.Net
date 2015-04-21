using System;
using System.Collections.Generic;
using SharpDX;

namespace PhysX.Samples
{
	public static class Mathematics
	{
		public static float Clamp(float value, float max, float min)
		{
			if (value < min)
				return min;
			if (value > max)
				return max;

			return value;
		}

		public static Vector3 DirectionFromViewMatrix(Matrix viewMatrix)
		{
			return Vector3.Normalize(new Vector3(viewMatrix.M13, viewMatrix.M23, viewMatrix.M33));
		}

		public static Vector3 DecomposeToPosition(Matrix matrix)
		{
			return new Vector3(matrix.M41, matrix.M42, matrix.M43);
		}
	}
}