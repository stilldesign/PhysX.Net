using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace StillDesign.PhysX.UnitTests
{
	/// <summary>
	/// Summary description for Scene_Description
	/// </summary>
	[TestClass]
	public class SceneDescriptionTests
	{
		public SceneDescriptionTests()
		{

		}

		public TestContext TestContext
		{
			get;
			set;
		}

		#region Additional test attributes
		//
		// You can use the following additional attributes as you write your tests:
		//
		// Use ClassInitialize to run code before running the first test in the class
		// [ClassInitialize()]
		// public static void MyClassInitialize(TestContext testContext) { }
		//
		// Use ClassCleanup to run code after all tests in a class have run
		// [ClassCleanup()]
		// public static void MyClassCleanup() { }
		//
		// Use TestInitialize to run code before running each test 
		// [TestInitialize()]
		// public void MyTestInitialize() { }
		//
		// Use TestCleanup to run code after each test has run
		// [TestCleanup()]
		// public void MyTestCleanup() { }
		//
		#endregion

		[TestMethod]
		public void MaximumBounds()
		{
			SceneDescription sceneDesc = new SceneDescription();

			try
			{
				sceneDesc.MaximumBounds = null;
				sceneDesc.MaximumBounds = new Bounds3( -10000.0f, -10000.0f, -10000.0f, 10000.0f, 10000.0f, 10000.0f );
				sceneDesc.MaximumBounds = new Bounds3( -10000.0f, -10000.0f, -10000.0f, 10000.0f, 10000.0f, 10000.0f );
				sceneDesc.MaximumBounds = null;
			}
			catch
			{
				Assert.Fail( "Setting SceneDescription.MaximumBounds Failed" );
			}
		}
	}
}