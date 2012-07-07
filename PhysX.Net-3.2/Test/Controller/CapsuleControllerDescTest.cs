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
					GroupsBitmask = 0xF0F0,
					Height = 101,
					InteractionMode = CCTInteractionMode.Include,
					InvisibleWallHeight = 102,
					Material = material,
					MaximumJumpHeight = 103,
					NonWalkableMode = CCTNonWalkableMode.PreventClimbing,
					Position = new Vector3(1, 2, 3),
					Radius = 104,
					ScaleCoefficient = 105,
					SlopeLimit = 106,
					StepOffset = 107,
					UpDirection = new Vector3(0, 0, 1),
					VolumeGrowth = 108
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
				Assert.AreEqual(1.5f, c.VolumeGrowth);
				Assert.AreEqual(null, c.Callback);
				Assert.AreEqual(null, c.UserData);
				Assert.AreEqual(CCTInteractionMode.Include, c.InteractionMode);
				Assert.AreEqual(CCTNonWalkableMode.PreventClimbing, c.NonWalkableMode);
				Assert.AreEqual(0xffffffff, c.GroupsBitmask);
				Assert.AreEqual(new Vector3(0, 0, 0), c.Position);
				Assert.AreEqual(null, c.Material);
				Assert.AreEqual(0, c.InvisibleWallHeight);
				Assert.AreEqual(0, c.MaximumJumpHeight);
			}
		}
	}
}