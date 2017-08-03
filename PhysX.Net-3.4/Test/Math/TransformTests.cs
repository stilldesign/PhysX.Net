using System;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class TransformTests
	{
		[TestMethod]
		public void ToMatrix_Position()
		{
			var a = new Transform(new Vector3(1, 2, 3));
			Assert.AreEqual(Matrix4x4.CreateTranslation(1, 2, 3), a.ToMatrix());
		}

		[TestMethod]
		public void ToMatrix_PositionAndQuat()
		{
			var a = new Transform(Quaternion.CreateFromYawPitchRoll(4, 5, 6), new Vector3(1, 2, 3));
			Assert.AreEqual(Matrix4x4.CreateFromYawPitchRoll(4, 5, 6) * Matrix4x4.CreateTranslation(1, 2, 3), a.ToMatrix());
		}

		[TestMethod]
		public void CastToMatrix4x4()
		{
			var a = new Transform(Quaternion.CreateFromYawPitchRoll(4, 5, 6), new Vector3(1, 2, 3));
			Assert.AreEqual(Matrix4x4.CreateFromYawPitchRoll(4, 5, 6) * Matrix4x4.CreateTranslation(1, 2, 3), (Matrix4x4)a);
		}

		[TestMethod]
		public void EqualsOperator_WithSelf()
		{
			var a = new Transform(new Vector3(1, 2, 3));

			Assert.IsTrue(a == a);
		}

		[TestMethod]
		public void EqualsOperator()
		{
			var a = new Transform(new Vector3(1, 2, 3));
			var b = new Transform(new Vector3(1, 2, 3));

			Assert.IsTrue(a == b);
		}

		[TestMethod]
		public void NotEqualsOperator()
		{
			var a = new Transform(new Vector3(1, 2, 3));
			var b = new Transform(new Vector3(4, 5, 6));

			Assert.IsTrue(a != b);
		}

		[TestMethod]
		public void GetHashCode_Differs()
		{
			var a = new Transform(new Vector3(1, 2, 3));
			var b = new Transform(new Vector3(4, 5, 6));

			Assert.AreNotEqual(a.GetHashCode(), b.GetHashCode());
		}
	}
}
