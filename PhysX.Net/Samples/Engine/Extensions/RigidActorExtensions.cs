using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PhysX.Samples
{
	public static class RigidActorExtensions
	{
		/// <summary>
		/// A convenience/backwards-compatability method.
		/// </summary>
		public static Shape CreateShape(this RigidActor actor, Geometry geometry, Material material)
		{
			return RigidActorExt.CreateExclusiveShape(actor, geometry, material);
		}
	}
}
