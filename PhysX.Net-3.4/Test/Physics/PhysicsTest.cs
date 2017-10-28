using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
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

		[TestMethod]
		public void OnMaterialAdded()
		{
			bool onMaterialAddedCalled = false;

			using (var physics = CreatePhysicsAndScene())
			{
				physics.Physics.OnMaterialAdded += mat =>
				{
					onMaterialAddedCalled = true;
				};

				var material = physics.Physics.CreateMaterial(10, 5, 0.5f);
			}

			Assert.IsTrue(onMaterialAddedCalled);
		}

		[TestMethod]
		public void OnMaterialRemoved()
		{
			bool onMaterialRemovedCalled = false;

			using (var physics = CreatePhysicsAndScene())
			{
				physics.Physics.OnMaterialRemoved += mat =>
				{
					onMaterialRemovedCalled = true;
				};

				var material = physics.Physics.CreateMaterial(10, 5, 0.5f);

				// Dispose a material should raise OnMaterialRemoved event
				material.Dispose();
			}

			Assert.IsTrue(onMaterialRemovedCalled);
		}

		/// <summary>
		/// Test getting all the created <see cref="PhysX.Joint"/> objects.
		/// </summary>
		[TestMethod]
		public void GetJoints()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);
				var rigid = physics.Physics.CreateRigidDynamic();

				var sphericalJoint = physics.Scene.CreateJoint<SphericalJoint>(rigid, Matrix4x4.Identity, null, Matrix4x4.Identity);

				var joints = physics.Physics.Joints;

				Assert.AreEqual(1, joints.Length);
				Assert.AreEqual(sphericalJoint, joints[0]);
			}
		}
	}
}