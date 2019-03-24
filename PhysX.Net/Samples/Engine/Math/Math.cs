using System;
using System.Collections.Generic;
using SharpDX;

namespace PhysX.Samples
{
	public static class Mathematics
	{
		public static Vector3 DirectionFromViewMatrix(Matrix viewMatrix)
		{
			return Vector3.Normalize(new Vector3(viewMatrix.M13, viewMatrix.M23, viewMatrix.M33));
		}
	}
}