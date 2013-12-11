using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;

namespace PhysX.Test
{
	[TestClass]
	public class PhysicsTest : Test
	{
		[TestMethod]
		public void CreateAndDisposePhysicsInstance()
		{
			using (var foundation = new Foundation(new ConsoleErrorCallback()))
			{
				Physics physics;
				using (physics = new Physics(foundation))
				{
					GC.Collect();

					Assert.IsFalse(physics.Disposed);
				}

				Assert.IsTrue(physics.Disposed);
			}
		}

		[TestMethod]
		public void ThrowsExceptionOnDuplicateInstantiation()
		{
			using (var foundation = new Foundation(new ConsoleErrorCallback()))
			{
				try
				{
					using (var physics = new Physics(foundation))
					{
						using (var physics2 = new Physics(foundation))
						{

						}
					}
					Assert.Fail("Creating multiple physics instances should throw an exception");
				}
				catch (PhysicsAlreadyInstantiatedException)
				{

				}
			}
		}

		/// <summary>
		/// This tests creating 10 materials and getting them back from Physics.Materials property.
		/// </summary>
		[TestMethod]
		public void CreateAndRetrieve10Materials()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var materials = new List<Material>();

				for (int i = 0; i < 10; i++)
				{
					var material = physics.Physics.CreateMaterial(10, 5, 0.5f);

					materials.Add(material);
				}

				foreach (var material in materials)
				{
					bool exists = physics.Physics.Materials.Contains(material);

					Assert.IsTrue(exists);
				}
			}
		}

		[TestMethod]
		public void VehicleSDKIsInitalized()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				Assert.IsNotNull(physics.Physics.VehicleSDK);
			}
		}
	}
}