using System;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class RigidActorTests : Test
	{
		[TestMethod]
		public void OnShapeAdded()
		{
			bool onShapeAddedCalled = false;

			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);

				var rigid = physics.Physics.CreateRigidDynamic();

				rigid.OnShapeAdded += s =>
				{
					onShapeAddedCalled = true;
				};

				var shape = rigid.CreateShape(new BoxGeometry(2, 2, 2), material);
			}

			Assert.IsTrue(onShapeAddedCalled);
		}

		[TestMethod]
		public void OnShapeRemoved()
		{
			bool onShapeRemovedCalled = false;

			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);

				var rigid = physics.Physics.CreateRigidDynamic();

				rigid.OnShapeRemoved += s =>
				{
					onShapeRemovedCalled = true;
				};

				var shape = rigid.CreateShape(new BoxGeometry(2, 2, 2), material);

				shape.Dispose();
			}

			Assert.IsTrue(onShapeRemovedCalled);
		}

		[TestMethod]
		public void CloneDynamic()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);

				var rigid = physics.Physics.CreateRigidDynamic();
				var box = rigid.CreateShape(new BoxGeometry(2, 3, 4), material);

				//

				var rigidClone = rigid.CloneDynamic(Matrix4x4.Identity, physics.Physics);

				//

				Assert.IsNotNull(rigidClone);
				Assert.AreEqual(1, rigidClone.Shapes.Count);
				Assert.AreEqual(GeometryType.Box, rigidClone.Shapes[0].GeometryType);
				Assert.AreEqual(material, rigidClone.Shapes[0].Materials[0]);
				Assert.AreNotEqual(box, rigidClone.Shapes[0]);
				Assert.AreEqual(new Vector3(2, 3, 4), rigidClone.Shapes[0].GetBoxGeometry().HalfExtents);
			}
		}
	}
}
