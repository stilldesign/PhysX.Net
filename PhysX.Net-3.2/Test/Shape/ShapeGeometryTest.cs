using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	[TestClass]
	public class ShapeGeometryTest : Test
	{
		private PhysicsAndSceneTestUnit _physics;
		private RigidDynamic _actor;
		private Material _material;

		[TestInitialize]
		public void TestInitalize()
		{
			_physics = CreatePhysicsAndScene();

			_material = _physics.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

			_actor = _physics.Physics.CreateRigidDynamic();

			_physics.Scene.AddActor(_actor);
		}
		[TestCleanup]
		public void TestCleanup()
		{
			_physics.Dispose();
			_physics = null;

			_actor = null;
		}

		[TestMethod]
		public void GetBoxGeometry()
		{
			var shape = _actor.CreateShape(new BoxGeometry(5, 5, 5), _material);

			var box = shape.GetBoxGeometry();

			Assert.IsNotNull(box);
			Assert.AreEqual(new Vector3(5, 5, 5), box.HalfExtents);
		}

		[TestMethod]
		public void GetSphereGeometry()
		{
			var shape = _actor.CreateShape(new SphereGeometry(88), _material);

			var sphere = shape.GetSphereGeometry();

			Assert.IsNotNull(sphere);
			Assert.AreEqual(88, sphere.Radius);
		}

		[TestMethod]
		public void GetCapsuleGeometry()
		{
			var shape = _actor.CreateShape(new CapsuleGeometry(radius: 12, halfHeight: 66), _material);

			var capsule = shape.GetCapsuleGeometry();

			Assert.IsNotNull(capsule);
			Assert.AreEqual(12, capsule.Radius);
			Assert.AreEqual(66, capsule.HalfHeight);
		}

		[TestMethod]
		public void GetPlaneGeometry()
		{
			var shape = _actor.CreateShape(new PlaneGeometry(), _material);

			var plane = shape.GetPlaneGeometry();

			Assert.IsNotNull(plane);
		}

		[TestMethod]
		public void GetHeightFieldGeometry()
		{
			throw new NotImplementedException();
		}

		[TestMethod]
		public void GetTriangleMeshGeometry()
		{
			throw new NotImplementedException();
		}
	}
}