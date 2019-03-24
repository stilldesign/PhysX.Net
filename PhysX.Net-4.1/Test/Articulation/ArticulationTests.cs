using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Articulation
{
	[TestClass]
	public class ArticulationTests : Test
	{
		[TestMethod]
		public void CreateAndDispose()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var a = physics.Physics.CreateArticulation();

				a.Dispose();
			}
		}
	}
}