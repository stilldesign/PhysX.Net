using System;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Joint
{
	[TestClass]
	public class JointTest : Test
	{
		[TestMethod]
		public void SetActors()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var box1 = CreateBoxActor(core.Scene, 0, 10, 0);
				var box2 = CreateBoxActor(core.Scene, 0, 20, 0);

				var box3 = CreateBoxActor(core.Scene, 10, 10, 0);
				var box4 = CreateBoxActor(core.Scene, 10, 20, 0);

				var joint = core.Scene.CreateJoint<RevoluteJoint>(box1, Matrix4x4.Identity, box2, Matrix4x4.Identity);

				Assert.AreEqual(box1, joint.Actor0);
				Assert.AreEqual(box2, joint.Actor1);

				joint.SetActors(box3, box4);

				Assert.AreEqual(box3, joint.Actor0);
				Assert.AreEqual(box4, joint.Actor1);
			}
		}
	}
}
