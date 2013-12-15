using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test.Geometry
{
	[TestClass]
	public class GeometryQueryTest
	{
		[TestMethod]
		public void Sweep()
		{
			var sweeper = new SphereGeometry(5);
			var obstacle = new SphereGeometry(3);

			var hit = GeometryQuery.Sweep
			(
				new Vector3(0, 0, 1),
				100,
				sweeper,
				Matrix.Translation(0, 5, 0),
				obstacle,
				Matrix.Translation(0, 5, 10)
			);

			Assert.IsNotNull(hit);
			Assert.AreEqual(2.0f, hit.Distance);
		}
	}
}