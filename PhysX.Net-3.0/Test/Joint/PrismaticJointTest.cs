using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

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

				using (var prismaticJoint = core.Scene.CreateJoint<PrismaticJoint>(box, Matrix.Identity, null, Matrix.Identity))
				{

				}
			}
		}
	}
}