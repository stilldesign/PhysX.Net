using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class ShapeTest : Test
	{
		[TestMethod]
		public void GetAndSetMaterialOfShape()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// New material to set
				var newMaterial = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);

				var actor = CreateBoxActor(physics.Scene, new Vector3(5, 5, 5), new Vector3(0, 0, 0));
				var boxShape = actor.Shapes.First();

				physics.Scene.AddActor(actor);

				// Assign the new material (can only be 1, given the shape setup)
				boxShape.Materials = new[] { newMaterial };

				Assert.AreEqual(1, boxShape.Materials.Length);
				Assert.AreEqual(newMaterial, boxShape.Materials[0]);
			}
		}

		[TestMethod]
		public void DisposingShapeRemovesItFromItsActor()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// Create an actor with a box shape
				var actor = CreateBoxActor(physics.Scene, new Vector3(5, 5, 5), new Vector3(0, 0, 0));

				Assert.AreEqual(1, actor.Shapes.Count());

				var boxShape = actor.Shapes.First();

				// Dispose that shape
				boxShape.Dispose();

				// Make sure the shape was removed from its parent actor because of the Dispose call
				Assert.AreEqual(0, actor.Shapes.Count());
				Assert.IsTrue(boxShape.Disposed);
			}
		}
	}
}