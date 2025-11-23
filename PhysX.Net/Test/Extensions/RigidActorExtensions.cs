namespace PhysX.Test;

	public static class RigidActorExtensions
	{
		/// <summary>
		/// A convenience/backwards-compatability method.
		/// </summary>
		public static Shape CreateShape(this RigidActor actor, PhysX.Geometry geometry, Material material)
		{
			return RigidActorExt.CreateExclusiveShape(actor, geometry, material);
		}
	}
