using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test.Controller
{
	[TestClass]
	public class CapsuleControllerDescTest : Test
	{
		[TestMethod]
		public void SetToDefault()
		{
			using (var physics = CreatePhysicsAndScene())
			{
				var material = physics.Physics.CreateMaterial(1, 2, 3);

				// Change all the properties of a CapsuleControllerDesc
				var c = new CapsuleControllerDesc()
				{
					ClimbingMode = CapsuleClimbingMode.Easy,
					ContactOffset = 99,
					Density = 100,
					Height = 101,
					Material = material,
					NonWalkableMode = ControllerNonWalkableMode.PreventClimbing,
					Position = new Vector3(1, 2, 3),
					Radius = 104,
					ScaleCoefficient = 105,
					SlopeLimit = 106,
					StepOffset = 107,
					UpDirection = new Vector3(0, 0, 1),
				};

				// Set the description to default
				c.SetToDefault();

				// Capsule
				Assert.AreEqual(CapsuleClimbingMode.Easy, c.ClimbingMode);
				Assert.AreEqual(0, c.Radius);
				Assert.AreEqual(0, c.Height);

				// ControllerDesc
				Assert.AreEqual(0.1f, c.ContactOffset);
				Assert.AreEqual(0.5f, c.StepOffset);
				Assert.AreEqual(10.0f, c.Density);
				Assert.AreEqual(0.8f, c.ScaleCoefficient);
				Assert.AreEqual(null, c.UserData);
				Assert.AreEqual(new Vector3(0, 0, 0), c.Position);
				Assert.AreEqual(null, c.Material);
			}
		}
	}
}