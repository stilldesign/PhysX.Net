using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Test.Util;

namespace PhysX.Test.Cooking
{
	[TestClass]
	public class CookingTriangleMeshTests : Test
	{
		[TestMethod]
		public void CookTriangleMesh()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// Create a grid of triangles to be our cloth
				var clothGrid = new VertexGrid(25, 25);

				using (var cooking = physics.Physics.CreateCooking())
				{
					var desc = new TriangleMeshDesc()
					{
						Points = clothGrid.Points,
						Triangles = clothGrid.Indices
					};

					var stream = new MemoryStream();

					var result = cooking.CookTriangleMesh(desc, stream);

					Assert.AreEqual(TriangleMeshCookingResult.Success, result);
				}
			}
		}
	}
}