using System;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class RigidActorTests : Test
	{
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

		[TestMethod]
		public void CreateShape_IsInActorsShapesProperty()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);
				var rigid = physics.Physics.CreateRigidDynamic();
				var box = rigid.CreateShape(new BoxGeometry(2, 3, 4), material);

				Assert.AreEqual(1, rigid.Shapes.Count);
			}
		}

		[TestMethod]
		public void CreateShape_DisposingOfShapeRemovesItFromActorsShapesProperty()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);
				var rigid = physics.Physics.CreateRigidDynamic();
				var box = rigid.CreateShape(new BoxGeometry(2, 3, 4), material);

				Assert.AreEqual(1, rigid.Shapes.Count);

				box.Dispose();

				Assert.AreEqual(0, rigid.Shapes.Count);
			}
		}

		[TestMethod]
		public void Shapes_CanReturnEmpty()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);
				var rigid = physics.Physics.CreateRigidDynamic();

				Assert.AreEqual(0, rigid.Shapes.Count);
			}
		}
	}
}
