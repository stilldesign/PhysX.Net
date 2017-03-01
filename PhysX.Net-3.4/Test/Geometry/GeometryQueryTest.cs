using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using Microsoft.VisualStudio.TestTools.UnitTesting;

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
				Matrix4x4.CreateTranslation(0, 5, 0),
				obstacle,
				Matrix4x4.CreateTranslation(0, 5, 10)
			);

			Assert.IsNotNull(hit);
			Assert.AreEqual(2.0f, hit.Distance);
		}

		[TestMethod]
		public void GetWorldBounds()
		{
			var sphere = new SphereGeometry(5);

			var bounds = GeometryQuery.GetWorldBounds(sphere, Matrix4x4.Identity);

			// We started with a sphere of radius 5,
			// the bounding size + inflation value (3rd optional arg) results
			// in a box of size 10.1 whd
			Assert.AreEqual(new Bounds3(new Vector3(10.1f, 10.1f, 10.1f)), bounds);
		}
	}
}