using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

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

				using (var d6 = core.Scene.CreateJoint<D6Joint>(box, Matrix4x4.Identity, null, Matrix4x4.Identity))
				{

				}
			}
		}
	}
}