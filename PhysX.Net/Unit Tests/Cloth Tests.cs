using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class ClothTests : TestBase
	{
		public ClothTests()
		{

		}

		[TestMethod]
		public void AllocateMeshData()
		{
			ClothDescription desc = new ClothDescription();

			desc.MeshData.AllocateParentIndices<int>( 100 );
		}
	}
}