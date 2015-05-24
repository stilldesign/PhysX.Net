using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;
using PhysX.Test.Util;

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
				using (var cooking = physics.Physics.CreateCooking())
				{
					var clothMeshDesc = new ClothMeshDesc()
					{
						Points = clothGrid.Points,
						Triangles = ArrayUtil.ToByteArray(clothGrid.Indices)
					};

					MemoryStream stream = new MemoryStream();

					cooking.CookClothFabric(clothMeshDesc, new Vector3(0, -9.81f, 0), stream);

					// After cooking the fabric, we must put the position of the written stream back to 0
					// so that it can be read from the beginning in the CreateClothFabric method
					stream.Position = 0;

					ClothFabric clothFabric = physics.Physics.CreateClothFabric(stream);

					ClothParticle[] particles = clothGrid.Points.Select(p => new ClothParticle(p, 2)).ToArray();

					Cloth cloth = physics.Physics.CreateCloth(Matrix.Identity, clothFabric, particles, 0);
				}
			}
		}

		[TestMethod]
		public void LockParticleDataToReadPositions()
		{
			var clothGrid = new ClothTestGrid(10, 10);

			using (var physics = CreatePhysicsAndScene())
			{
				using (var cooking = physics.Physics.CreateCooking())
				{
					var clothMeshDesc = new ClothMeshDesc()
					{
						Points = clothGrid.Points,
						Triangles = ArrayUtil.ToByteArray(clothGrid.Indices)
					};

					MemoryStream stream = new MemoryStream();

					cooking.CookClothFabric(clothMeshDesc, new Vector3(0, -9.81f, 0), stream);

					// After cooking the fabric, we must put the position of the written stream back to 0
					// so that it can be read from the beginning in the CreateClothFabric method
					stream.Position = 0;

					ClothFabric clothFabric = physics.Physics.CreateClothFabric(stream);

					ClothParticle[] particles = clothGrid.Points.Select(p => new ClothParticle(p, 2)).ToArray();

					Cloth cloth = physics.Physics.CreateCloth(Matrix.Identity, clothFabric, particles, 0);

					var read = cloth.LockParticleData();

					// Are the particle positions the right length
					Assert.AreEqual(121, read.Particles.Length);

					// And initially is what we read back the same as what we started with
					for (int i = 0; i < 121; i++)
					{
						Assert.AreEqual(clothGrid.Points[i], read.Particles[i].Position);
					}
				}
			}
		}
	}
}