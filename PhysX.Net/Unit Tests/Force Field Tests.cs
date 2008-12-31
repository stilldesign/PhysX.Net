using System;
using System.Linq;
using System.Collections.Generic;

using Microsoft.VisualStudio.TestTools.UnitTesting;

#if GRAPHICS_XNA2 || GRAPHICS_XNA3
using Microsoft.Xna.Framework;
#elif GRAPHICS_MDX
using Microsoft.DirectX;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

using StillDesign.PhysX;

namespace StillDesign.PhysX.UnitTests
{
	/// <summary>
	/// Summary description for ForceFieldTests
	/// </summary>
	[TestClass]
	public class ForceFieldTests : TestBase
	{
		public ForceFieldTests()
		{

		}

		private TestContext testContextInstance;

		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		public TestContext TestContext
		{
			get
			{
				return testContextInstance;
			}
			set
			{
				testContextInstance = value;
			}
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
		public void CreateBoxForceField()
		{
			BoxForceFieldShapeDescription boxForceFieldShapeDesc = new BoxForceFieldShapeDescription()
			{
				Size = new Vector3( 10, 10, 10 )
			};

			ForceFieldLinearKernelDescription kernelDesc = new ForceFieldLinearKernelDescription()
			{
				Constant = new Vector3( 0, 100.0f, 0 )
			};

			ForceFieldLinearKernel kernel = this.Scene.CreateForceFieldLinearKernel( kernelDesc );

			ForceFieldShapeGroupDescription shapeGroupDesc = new ForceFieldShapeGroupDescription()
			{
				Shapes = { boxForceFieldShapeDesc }
			};

			ForceFieldShapeGroup shapeGroup = this.Scene.CreateForceFieldShapeGroup( shapeGroupDesc );

			BoxForceFieldShape boxForceFieldShape = shapeGroup.CreateShape( boxForceFieldShapeDesc ) as BoxForceFieldShape;
			boxForceFieldShape.Pose = GraphicsLibraryWrapper.CreateTranslationMatrix( new Vector3( 30, 5, 0 ) );

			ForceFieldDescription forceFieldDesc = new ForceFieldDescription()
			{
				Kernel = kernel,
				ShapeGroups = { shapeGroup }
			};

			ForceField forceField = this.Scene.CreateForceField( forceFieldDesc );
		}
	}
}
