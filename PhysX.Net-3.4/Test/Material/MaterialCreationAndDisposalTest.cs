using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class MaterialCreationAndDisposalTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeMaterial()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				Assert.IsFalse(material.Disposed);

				material.Dispose();

				Assert.IsTrue(material.Disposed);
			}
		}

		[TestMethod]
		public void CreateMultipleMaterials()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				for (int i = 0; i < 10; i++)
				{
					var materialN = physics.Physics.CreateMaterial(5, 6, 7);
				}
			}
		}

		[TestMethod]
		public void MultipleDisposalCallsAreValid()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(5, 6, 7);

				Assert.IsFalse(material.Disposed);

				material.Dispose();

				Assert.IsTrue(material.Disposed);

				material.Dispose();

				Assert.IsTrue(material.Disposed);
			}
		}
	}
}