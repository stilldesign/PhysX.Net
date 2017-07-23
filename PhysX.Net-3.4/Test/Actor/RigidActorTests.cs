using System;
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
	}
}
