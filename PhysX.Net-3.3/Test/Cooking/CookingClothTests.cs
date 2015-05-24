using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;
using PhysX.Test.Util;

namespace PhysX.Test.Cooking
{
	[TestClass]
	public class CookingClothTests : Test
	{
		[TestMethod]
		public void CookClothFabric()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				// Create a grid of triangles to be our cloth
				var clothGrid = new VertexGrid(25, 25);

				using (var cooking = physics.Physics.CreateCooking())
				{
					ClothMeshDesc clothMeshDesc = new ClothMeshDesc()
					{
						Points = clothGrid.Points,
						Triangles = ArrayUtil.ToByteArray(clothGrid.Indices)
					};

					var stream = new MemoryStream();

					cooking.CookClothFabric(clothMeshDesc, new Vector3(0, -9.81f, 0), stream);
				}
			}
		}

		/// <summary>
		/// The simplest possible set of data to make debugging the cooker logic and math easy.
		/// 3 points, 1 triangle.
		/// </summary>
		[TestMethod]
		public void CookClothFabric_SimplestExample()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var points = new[] 
				{
					new Vector3(0, 5, 0),
					new Vector3(0, 5, 1),
					new Vector3(1, 5, 1)
				};

				var indices = new[] { 0, 1, 2 };

				using (var cooking = physics.Physics.CreateCooking())
				{
					var clothMeshDesc = new ClothMeshDesc()
					{
						Points = points,
						Triangles = ArrayUtil.ToByteArray(indices)
					};

					var stream = new MemoryStream();

					cooking.CookClothFabric(clothMeshDesc, new Vector3(0, -9.81f, 0), stream);
				}
			}
		}
	}
}