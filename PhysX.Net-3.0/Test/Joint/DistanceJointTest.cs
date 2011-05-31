using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class DistanceJointTest : Test
	{
		[TestMethod]
		public void CreateAndDisposeDistanceJoint()
		{
			using (CreatePhysicsAndScene())
			{
				var box = CreateBoxActor(5, 5, 5);

				var lf0 = Matrix.Translation(1, 2, 3);
				var lf1 = Matrix.Translation(3, 2, 1);

				using (var distance = this.Scene.CreateJoint<DistanceJoint>(box, lf0, null, lf1))
				{

				}
			}
		}
	}
}