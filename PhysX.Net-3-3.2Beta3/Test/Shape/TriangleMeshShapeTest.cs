using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;
using System.IO;

namespace PhysX.Test
{
	[TestClass]
	public class TriangleMeshShapeTest : Test
	{
		[TestMethod]
		public void CreateTriangleMeshShape()
		{
			var physics = CreatePhysicsAndScene();

			var material = physics.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

			var actor = physics.Physics.CreateRigidDynamic();

			var grid = new ClothTestGrid(10, 10);

			var triangleMeshDesc = new TriangleMeshDesc();
			triangleMeshDesc.Points = grid.Points;
			triangleMeshDesc.SetTriangles(grid.Indices);

			var cooking = physics.Physics.CreateCooking();

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