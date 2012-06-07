using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

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

				using (var fixedJoint = core.Scene.CreateJoint<FixedJoint>(box, Matrix.Identity, null, Matrix.Identity))
				{

				}
			}
		}
	}
}