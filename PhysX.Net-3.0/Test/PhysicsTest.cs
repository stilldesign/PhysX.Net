using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;

namespace PhysX.Test
{
	[TestClass]
	public class PhysicsTest : Test
	{
		[TestMethod]
		public void CreateAndDisposePhysicsInstance()
		{
			var physics = new Physics();

			GC.Collect();

			Assert.IsFalse(physics.Disposed);

			physics.Dispose();

			Assert.IsTrue(physics.Disposed);
		}
	}
}