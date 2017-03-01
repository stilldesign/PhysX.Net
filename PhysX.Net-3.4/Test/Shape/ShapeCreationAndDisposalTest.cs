using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class ShapeCreationAndDisposalTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeShape()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

				var actor = physics.Physics.CreateRigidDynamic();

				var shape = actor.CreateShape(new BoxGeometry(5, 5, 5), material);

				physics.Scene.AddActor(actor);

				Assert.IsFalse(shape.Disposed);

				shape.Dispose();

				Assert.IsTrue(shape.Disposed);
			}
		}
	}
}