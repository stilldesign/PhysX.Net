using System;
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Cooking
{
	[TestClass]
	public class CookingTests : Test
	{
		[TestMethod]
		public void CreateAndDisposeCooking()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				using (var cooking = physics.Physics.CreateCooking())
				{
					
				}
			}
		}

		[TestMethod]
		public void MidphaseType33()
		{
			var midphase33 = new MidphaseDesc
			{
				Bvh33Desc = new Bvh33MidphaseDesc()
			};

			Assert.AreEqual(MeshMidPhase.BoundingVolumeHierarchy33, midphase33.Type);
		}

		[TestMethod]
		public void MidphaseType34()
		{
			var midphase34 = new MidphaseDesc
			{
				Bvh34Desc = new Bvh34MidphaseDesc()
			};

			Assert.AreEqual(MeshMidPhase.BoundingVolumeHierarchy34, midphase34.Type);
		}
	}
}
