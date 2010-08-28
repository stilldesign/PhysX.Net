using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class DescriptionTests : TestBase
	{
		[TestMethod]
		public void CheckValid()
		{
			// Some basic tests to make sure the CheckValid function is being called

			ClothDescription clothDesc = new ClothDescription();

			Assert.AreEqual( 2, clothDesc.CheckValid() );
			Assert.AreEqual( 2, ((Description)clothDesc).CheckValid() );

			//

			SphericalJointDescription sphericalJointDesc = new SphericalJointDescription();

			Assert.AreEqual( 1, sphericalJointDesc.CheckValid() );
			Assert.AreEqual( 1, ((JointDescription)sphericalJointDesc).CheckValid() );
			Assert.AreEqual( 1, ((Description)sphericalJointDesc).CheckValid() );
		}
	}
}