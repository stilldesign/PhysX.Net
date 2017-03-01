using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class TriangleMeshShapeTest : Test
	{
		[TestMethod]
		public void CreateTriangleMeshShape()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

				var actor = physics.Physics.CreateRigidDynamic();

				// Triangle mesh can only be created on a kinematic actor
				actor.Flags = RigidDynamicFlags.Kinematic;

				var grid = new ClothTestGrid(10, 10);

				var triangleMeshDesc = new TriangleMeshDesc();
				triangleMeshDesc.Points = grid.Points;
				triangleMeshDesc.SetTriangles(grid.Indices);

				using (var cooking = physics.Physics.CreateCooking())
				{
					var cookedStream = new MemoryStream();

					bool result = cooking.CookTriangleMesh(triangleMeshDesc, cookedStream);

					Assert.IsTrue(result);

					cookedStream.Position = 0;

					var triangleMesh = physics.Physics.CreateTriangleMesh(cookedStream);

					var triangleMeshGeometry = new TriangleMeshGeometry(triangleMesh);

					var shape = actor.CreateShape(triangleMeshGeometry, material);

					physics.Scene.AddActor(actor);
				}
			}
		}
	}
}