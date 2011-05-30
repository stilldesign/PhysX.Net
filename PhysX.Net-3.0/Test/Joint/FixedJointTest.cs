using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.MathPrimitives;

namespace PhysX.Test
{
	[TestClass]
	public class FixedJointTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeFixedJoint()
		{
			using (CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(5, 5, 5);

				using (var fixedJoint = this.Scene.CreateJoint<FixedJoint>(box, Matrix.Identity, null, Matrix.Identity))
				{

				}
			}
		}
	}
}