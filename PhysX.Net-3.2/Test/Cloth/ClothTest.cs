using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class ClothTest : Test
	{
		[TestMethod]
		public void CreateFlag()
		{
			var clothGrid = new ClothTestGrid(10, 10);

			using (var physics = CreatePhysicsAndScene())
			{
				Cooking cooking = physics.Physics.CreateCooking();

				ClothMeshDesc clothMeshDesc = new ClothMeshDesc()
				{
					Points = clothGrid.Points,
					Triangles = clothGrid.Indices
				};

				MemoryStream stream = new MemoryStream();

				bool result = cooking.CookClothFabric(clothMeshDesc, new Vector3(0, -9.81f, 0), stream);

				ClothFabric clothFabric = physics.Physics.CreateClothFabric(stream);

				ClothParticle[] particles = clothGrid.Points.Select(p => new ClothParticle(p, 2)).ToArray();

				ClothCollisionData collision = new ClothCollisionData();

				Cloth cloth = physics.Physics.CreateCloth(Matrix.Identity, clothFabric, particles, collision, 0);
			}
		}
	}
}