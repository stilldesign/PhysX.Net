using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class HeightFieldSimpleTests : Test
	{
		private HeightField _heightField;
		private PhysicsAndSceneTestUnit _physics;

		[TestInitialize]
		public void SetupHeightField()
		{
			_physics = CreatePhysicsAndScene();

			const int rows = 25, columns = 40;
			var samples = HeightFieldTestUtil.CreateSampleGrid(rows, columns);

			var heightFieldDesc = new HeightFieldDesc()
			{
				NumberOfRows = rows,
				NumberOfColumns = columns,
				Samples = samples,
				Thickness = 4.2f,
				ConvexEdgeThreshold = 6.6f,
				Flags = HeightFieldFlag.NoBoundaryEdges
			};

			_heightField = _physics.Physics.CreateHeightField(heightFieldDesc);

			Assert.IsNotNull(_heightField);
			Assert.IsFalse(_heightField.Disposed);
		}
		[TestCleanup]
		public void Cleanup()
		{
			_heightField.Dispose();
			_heightField = null;

			_physics.Dispose();
			_physics = null;
		}

		[TestMethod]
		public void GetNumberOfRows()
		{
			Assert.AreEqual(25, _heightField.NumberOfRows);
		}

		[TestMethod]
		public void GetNumberOfColumns()
		{
			Assert.AreEqual(40, _heightField.NumberOfColumns);
		}

		[TestMethod]
		public void GetFormat()
		{
			Assert.AreEqual(HeightFieldFormat.Signed16BitIntegersWithTriangleMaterials, _heightField.Format);
		}

		[TestMethod]
		public void GetThickness()
		{
			Assert.AreEqual(4.2f, _heightField.Thickness);
		}

		[TestMethod]
		public void GetConvexEdgeThreshold()
		{
			Assert.AreEqual(6.6f, _heightField.ConvexEdgeThreshold);
		}

		[TestMethod]
		public void GetFlags()
		{
			Assert.AreEqual(HeightFieldFlag.NoBoundaryEdges, _heightField.Flags);
		}

		[TestMethod]
		public void GetHeight()
		{
			Assert.AreEqual(-5, _heightField.GetHeight(2.0f, 3.0f));
		}

		[TestMethod]
		public void GetConcreteTypeName()
		{
			Assert.AreEqual("PxHeightField", _heightField.AsSerializable().ConcreteTypeName);
		}
	}
}