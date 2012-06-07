using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class D6JointTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeD6Joint()
		{
			using (var core = CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(core.Scene, 5, 5, 5);

				using (var d6 = core.Scene.CreateJoint<D6Joint>(box, Matrix.Identity, null, Matrix.Identity))
				{

				}
			}
		}
	}
}