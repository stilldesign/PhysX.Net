using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Samples.Engine
{
	public static class MathExtensions
	{
		public static SlimDX.Vector3 AsSlimDX(this PhysX.Math.Vector3 vector3)
		{
			return new SlimDX.Vector3(vector3.X, vector3.Y, vector3.Z);
		}

		public static PhysX.Math.Vector3 AsPhysX(this SlimDX.Vector3 vector3)
		{
			return new PhysX.Math.Vector3(vector3.X, vector3.Y, vector3.Z);
		}

		public static PhysX.Math.Matrix AsPhysX(this SlimDX.Matrix m)
		{
			return new Math.Matrix
			(
				m.M11, m.M12, m.M13, m.M14,
				m.M21, m.M22, m.M23, m.M24,
				m.M31, m.M32, m.M33, m.M34,
				m.M41, m.M42, m.M43, m.M44
			);
		}
	}
}