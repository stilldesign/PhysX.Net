using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.MathPrimitives;

namespace PhysX.Test
{
	[TestClass]
	public class D6JointTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeD6Joint()
		{
			using (CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(5, 5, 5);

				using (var d6 = this.Scene.CreateJoint<D6Joint>(box, Matrix.Identity, null, Matrix.Identity))
				{

				}
			}
		}
	}
}