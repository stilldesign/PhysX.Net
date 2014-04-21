using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Tests
{
	[TestClass]
	public class ControllerTests : TestBase
	{
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

				Assert.IsTrue( boxController.IsDisposed );
				Assert.IsTrue( manager.Controllers.Count == 0 );
			}
		}

		[TestMethod]
		public void CreateMultipleControllers()
		{
			using( CreateCoreAndScene() )
			{
				ControllerManager manager = this.Scene.CreateControllerManager();

				BoxControllerDescription descA = new BoxControllerDescription( new Vector3( 1.0f, 1.0f, 1.0f ), Vector3.Zero );
				BoxController boxControllerA = manager.CreateController( descA ) as BoxController;
				boxControllerA.Dispose();

				BoxControllerDescription descB = new BoxControllerDescription( new Vector3( 1.0f, 1.0f, 1.0f ), Vector3.Zero );
				BoxController boxControllerB = manager.CreateController( descB ) as BoxController;
			}
		}
	}
}