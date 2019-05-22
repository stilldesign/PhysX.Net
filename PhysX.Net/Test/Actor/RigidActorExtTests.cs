using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Actor
{
	[TestClass]
	public class RigidActorExtTests : Test
	{
		[TestMethod]
		public void CreateExclusiveShape_IsInActorsShapesProperty()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(0.2f, 0.1f, 0.2f);
				var rigid = physics.Physics.CreateRigidDynamic();

				Assert.AreEqual(0, rigid.Shapes.Count);

				var box = RigidActorExt.CreateExclusiveShape(rigid, new BoxGeometry(2, 3, 4), material);

				Assert.AreEqual(1, rigid.Shapes.Count);
			}
		}
	}
}
