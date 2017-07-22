using System;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	public class ClothMeshQuadifierTests
	{
		[TestMethod]
		public void Quadifier()
		{
			var foundation = new Foundation();

			// Indices - 2 triangles
			/*
				1_____2
				|    /|
				|   / |
				|  /  |
				| /   |
				0 ____3
			*/
			var indices = new short[]
			{
				0, 1, 2,
				0, 2, 3
			};

			var clothMeshDesc = new ClothMeshDesc
			{
				Flags = MeshFlag.FlipNormals | MeshFlag.Indices16Bit,
				InverseMasses = new float[] { 1, 2, 3, 4 },
				Points = new[]
				{
					new Vector3(0, 0, 0),
					new Vector3(0, 10, 0),
					new Vector3(10, 10, 0),
					new Vector3(10, 0, 0)
				},
				Triangles = Util.ArrayUtil.ToByteArray(indices)
			};

			// This should turn the two triangles into a single quad
			var quad = ClothMeshQuadifier.GetDescriptor(clothMeshDesc);

			Assert.IsNotNull(quad);
			Assert.IsNotNull(quad.Quads);

			// Quad indices are (currently) always Int32
			var quads = quad.GetQuads32();
			Assert.AreEqual(4, quads.Length);
			Assert.AreEqual(0, quads[0]);
			Assert.AreEqual(1, quads[1]);
			Assert.AreEqual(2, quads[2]);
			Assert.AreEqual(3, quads[3]);
		}
	}
}
