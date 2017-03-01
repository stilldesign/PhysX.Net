using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

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

			// Make the actor kinematic because Triangle mesh, heightfield and plane geometry shapes require it.
			_actor.RigidBodyFlags = RigidBodyFlag.Kinematic;

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
			var material = _physics.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

			const int rows = 25, columns = 25;
			var samples = HeightFieldTestUtil.CreateSampleGrid(rows, columns);

			var heightFieldDesc = new HeightFieldDesc()
			{
				NumberOfRows = rows,
				NumberOfColumns = columns,
				Samples = samples
			};

			var cooking = _physics.Physics.CreateCooking();

			var stream = new MemoryStream();
			bool cookResult = cooking.CookHeightField(heightFieldDesc, stream);

			var heightField = _physics.Physics.CreateHeightField(stream);

			Assert.IsNotNull(heightField);

			var heightFieldGeometry = new HeightFieldGeometry
			(
				heightField: heightField,
				flags: MeshGeometryFlag.DoubleSided,
				heightFieldScale: 2.3f,
				rowScale: 1.2f,
				columnScale: 1.9f
			);

			var shape = _actor.CreateShape(heightFieldGeometry, material);

			//

			var retrievedHeightfieldGeom = shape.GetHeightFieldGeometry();

			Assert.IsNotNull(retrievedHeightfieldGeom);
			Assert.AreEqual(heightField, retrievedHeightfieldGeom.HeightField);
			Assert.AreEqual(retrievedHeightfieldGeom.ColumnScale, 1.9f);
			Assert.AreEqual(retrievedHeightfieldGeom.RowScale, 1.2f);
			Assert.AreEqual(retrievedHeightfieldGeom.HeightFieldFlags, MeshGeometryFlag.DoubleSided);
		}

		[TestMethod]
		public void GetTriangleMeshGeometry()
		{
			var material = _physics.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

			var actor = _physics.Physics.CreateRigidDynamic();

			// Triangle mesh can only be created on a kinematic actor
			actor.RigidBodyFlags = RigidBodyFlag.Kinematic;

			var grid = new ClothTestGrid(10, 10);

			var triangleMeshDesc = new TriangleMeshDesc();
			triangleMeshDesc.Points = grid.Points;
			triangleMeshDesc.SetTriangles(grid.Indices);

			MemoryStream cookedStream;
			using (var cooking = _physics.Physics.CreateCooking())
			{
				cookedStream = new MemoryStream();

				bool result = cooking.CookTriangleMesh(triangleMeshDesc, cookedStream);

				Assert.IsTrue(result);

				cookedStream.Position = 0;
			}

			var triangleMesh = _physics.Physics.CreateTriangleMesh(cookedStream);

			var triangleMeshGeometry = new TriangleMeshGeometry(triangleMesh);

			var shape = actor.CreateShape(triangleMeshGeometry, material);

			//

			var retrievedTriangleMeshGeom = shape.GetTriangleMeshGeometry();

			Assert.IsNotNull(retrievedTriangleMeshGeom);
			Assert.AreEqual(triangleMesh, retrievedTriangleMeshGeom.TriangleMesh);
			Assert.AreEqual(GeometryType.TriangleMesh, retrievedTriangleMeshGeom.Type);
			Assert.AreEqual(new MeshScale(new Vector3(1), Quaternion.Identity), retrievedTriangleMeshGeom.Scale);
			Assert.AreEqual((MeshGeometryFlag)0, retrievedTriangleMeshGeom.MeshFlags);
		}
	}
}