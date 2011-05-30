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
			Physics physics;
			using (physics = new Physics())
			{
				GC.Collect();

				Assert.IsFalse(physics.Disposed);
			}

			Assert.IsTrue(physics.Disposed);
		}

		[TestMethod]
		public void ThrowsExceptionOnDuplicateInstantiation()
		{
			try
			{
				using (var physics = new Physics())
				{
					using (var physics2 = new Physics())
					{

					}
				}
				Assert.Fail("Creating multiple physics instances should throw an exception");
			}
			catch (PhysicsAlreadyInstantiatedException)
			{

			}
		}
	}
}