using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public static class ForceFieldSample
	{
		public static PhysX.ForceField CreateForceField(Scene scene)
		{
			var boxForceFieldShapeDesc = new BoxForceFieldShapeDescription()
			{
				Size = new Vector3(10, 10, 10)
			};

			var kernelDesc = new ForceFieldLinearKernelDescription()
			{
				Constant = new Vector3(0, 100, 0)
			};

			var kernel = scene.CreateForceFieldLinearKernel(kernelDesc);

			var shapeGroupDesc = new ForceFieldShapeGroupDescription()
			{
				Shapes = { boxForceFieldShapeDesc }
			};

			var shapeGroup = scene.CreateForceFieldShapeGroup(shapeGroupDesc);

			var boxForceFieldShape = shapeGroup.CreateShape(boxForceFieldShapeDesc) as BoxForceFieldShape;
			boxForceFieldShape.Pose = Matrix.Translation(30, 5, 0);

			var forceFieldDesc = new ForceFieldDescription()
			{
				Kernel = kernel,
				ShapeGroups = { shapeGroup }
			};

			var forceField = scene.CreateForceField(forceFieldDesc);

			return forceField;
		}
	}
}