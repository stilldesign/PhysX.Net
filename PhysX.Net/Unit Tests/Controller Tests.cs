using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
#if GRAPHICS_XNA31
using Microsoft.Xna.Framework;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public class ControllerTests : TestBase
	{
		public ControllerTests()
		{

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
		public void DisposeOfBoxController()
		{
			using( CreateCoreAndScene() )
			{
				var manager = this.Scene.CreateControllerManager();

				var boxControllerDesc = new BoxControllerDescription( 2, 5, 2 )
				{

				};

				var boxController = manager.CreateController( boxControllerDesc ) as BoxController;

				boxController.Dispose();

				GC.Collect();

				Assert.IsTrue( boxController.IsDisposed == true );
				Assert.IsTrue( manager.Controllers.Count == 0 );
			}
		}

		[TestMethod]
		public void CreateMultipleControllers()
		{
			using( CreateCoreAndScene() )
			{
				ControllerManager manager = this.Scene.CreateControllerManager();

				BoxControllerDescription descA = new BoxControllerDescription( new Vector3( 1.0f, 1.0f, 1.0f ), GraphicsLibraryWrapper.Vector3Empty );
				BoxController boxControllerA = manager.CreateController( descA ) as BoxController;
				boxControllerA.Dispose();

				BoxControllerDescription descB = new BoxControllerDescription( new Vector3( 1.0f, 1.0f, 1.0f ), GraphicsLibraryWrapper.Vector3Empty );
				BoxController boxControllerB = manager.CreateController( descB ) as BoxController;
			}
		}
	}
}