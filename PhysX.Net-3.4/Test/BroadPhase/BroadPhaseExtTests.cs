using System;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class BroadPhaseExtTests
	{
		[TestMethod]
		public void CreateRegionsFromWorldBounds()
		{
			var bounds = BroadPhaseExt.CreateRegionsFromWorldBounds(new Bounds3(new Vector3(10)), 3);

			Assert.IsNotNull(bounds);
			Assert.AreEqual(9, bounds.Length);
		}
	}
}
