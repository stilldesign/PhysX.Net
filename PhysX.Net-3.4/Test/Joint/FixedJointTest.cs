using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class FixedJointTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeFixedJoint()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(core.Scene, 5, 5, 5);

				using (var fixedJoint = core.Scene.CreateJoint<FixedJoint>(box, Matrix4x4.Identity, null, Matrix4x4.Identity))
				{

				}
			}
		}
	}
}