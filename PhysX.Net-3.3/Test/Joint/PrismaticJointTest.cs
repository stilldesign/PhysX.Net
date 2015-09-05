using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class PrismaticJointTest : Test
	{
		[TestMethod]
		public void CreateAndDisposePrismaticJoint()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(core.Scene, 5, 5, 5);

				var prismaticJoint = core.Scene.CreateJoint<PrismaticJoint>(box, Matrix4x4.Identity, null, Matrix4x4.Identity);

				prismaticJoint.Dispose();
			}
		}

		[TestMethod]
		public void DisposeOfOnlyAttachedActor()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(core.Scene, 5, 5, 5);

				var prismaticJoint = core.Scene.CreateJoint<PrismaticJoint>(box, Matrix4x4.Identity, null, Matrix4x4.Identity);

				Assert.IsNotNull(prismaticJoint.Actor0);

				box.Dispose();

				Assert.IsNull(prismaticJoint.Actor0);
			}
		}
	}
}