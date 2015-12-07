using System;
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;
using PhysX.Test.Util;

namespace PhysX.Test.Cooking
{
	[TestClass]
	public class CookingTests : Test
	{
		[TestMethod]
		public void CreateAndDisposeCooking()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				using (var cooking = physics.Physics.CreateCooking())
				{
					
				}
			}
		}
	}
}
