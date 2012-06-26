using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class ShapeTest : Test
	{
		private Shape _shape;
		private PhysicsAndSceneTestUnit _physics;

		[TestInitialize]
		public void TestInitalize()
		{
			_physics = CreatePhysicsAndScene();

			var material = _physics.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

			var actor = _physics.Physics.CreateRigidDynamic();

			_shape = actor.CreateShape(new BoxGeometry(5, 5, 5), material);

			_physics.Scene.AddActor(actor);
		}
		[TestCleanup]
		public void TestCleanup()
		{
			_physics.Dispose();
			_physics = null;

			_shape = null;
		}
	}
}