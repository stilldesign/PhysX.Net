using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Tests
{
	[TestClass]
	public class ForceFieldTests : TestBase
	{
		[TestMethod]
		public void CreateBoxForceField()
		{
			using( CreateCoreAndScene() )
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
				boxForceFieldShape.Pose = Matrix.Translation( new Vector3( 30, 5, 0 ) );

				ForceFieldDescription forceFieldDesc = new ForceFieldDescription()
				{
					Kernel = kernel,
					ShapeGroups = { shapeGroup }
				};

				ForceField forceField = this.Scene.CreateForceField( forceFieldDesc );
			}
		}
	}
}