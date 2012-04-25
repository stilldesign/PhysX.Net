using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PhysX.Samples;
using PhysX.Math;
using PhysX.Samples.Engine;
using System.IO;

namespace PhysX.Samples.RigidBodiesSample
{
	public class RigidBodiesSample : Sample
	{
		public RigidBodiesSample()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var material = scene.Physics.CreateMaterial(0.7f, 0.7f, 0.1f);

			// Boxes
			CreateBoxes(scene, material);

			// Spheres
			CreateSpheres(scene, material);

			// Capsule
			CreateCapsules(scene, material);

			// HeightField
			CreateHeightField(scene, material);

			// Triangle Mesh
			CreateTriangleMesh(scene, material);

			// Convex mesh
			CreateConvexMesh(scene, material);
		}

		private static void CreateBoxes(Scene scene, Material material)
		{
			for (int i = 0; i < 10; i++)
			{
				var rigidActor = scene.Physics.CreateRigidDynamic();

				var boxGeom = new BoxGeometry(2, 2, 2);
				var boxShape = rigidActor.CreateShape(boxGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(-20, 10 + i * (boxGeom.Size.Y + 0.5f), 0);
				rigidActor.SetMassAndUpdateInertia(10);

				scene.AddActor(rigidActor);
			}
		}

		private static void CreateSpheres(Scene scene, Material material)
		{
			for (int i = 0; i < 10; i++)
			{
				var rigidActor = scene.Physics.CreateRigidDynamic();

				var sphereGeom = new SphereGeometry(radius: 2);
				var boxShape = rigidActor.CreateShape(sphereGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(-10, 30 + i * (sphereGeom.Radius * 2 + 0.5f), 0);
				rigidActor.SetMassAndUpdateInertia(10);

				scene.AddActor(rigidActor);
			}
		}

		private static void CreateCapsules(Scene scene, Material material)
		{
			for (int i = 0; i < 10; i++)
			{
				var rigidActor = scene.Physics.CreateRigidDynamic();

				var capsuleGeom = new CapsuleGeometry(radius: 2, halfHeight: 2);
				var boxShape = rigidActor.CreateShape(capsuleGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(0, 30 + i * (capsuleGeom.HalfHeight + capsuleGeom.Radius + 0.5f), 0);
				rigidActor.SetMassAndUpdateInertia(10);

				scene.AddActor(rigidActor);
			}
		}

		private void CreateHeightField(Scene scene, Material material)
		{
			const int rows = 25, columns = 25;
			const float scale = 3;

			var samples = CreateSampleGrid(rows, columns);

			var heightFieldDesc = new HeightFieldDesc()
			{
				NumberOfRows = rows,
				NumberOfColumns = columns,
				Samples = samples
			};

			HeightField heightField = scene.Physics.CreateHeightField(heightFieldDesc);

			//

			var rigidActor = scene.Physics.CreateRigidStatic();

			var heightFieldGeom = new HeightFieldGeometry(heightField, MeshGeometryFlag.DoubleSided, 1, scale, scale);

			rigidActor.CreateShape(heightFieldGeom, material);

			rigidActor.GlobalPose = Matrix.Translation(30, 30, -32.5f);

			scene.AddActor(rigidActor);
		}

		private void CreateTriangleMesh(Scene scene, Material material)
		{
			var colladaLoader = new ColladaLoader();
			var bunny = colladaLoader.Load(@"Teapot.DAE", this.Engine.GraphicsDevice);

			var triangleMeshDesc = new TriangleMeshDesc()
			{
				Flags = (MeshFlag)0,
				Triangles = bunny.Indices,
				Points = bunny.VertexPositions
			};

			var cooking = scene.Physics.CreateCooking();

			var stream = new MemoryStream();
			bool cookResult = cooking.CookTriangleMesh(triangleMeshDesc, stream);

			stream.Position = 0;

			var triangleMesh = scene.Physics.CreateTriangleMesh(stream);

			var triangleMeshGeom = new TriangleMeshGeometry(triangleMesh)
			{
				Scale = new MeshScale(new Vector3(0.3f, 0.3f, 0.3f), Quaternion.Identity)
			};

			var rigidActor = scene.Physics.CreateRigidStatic();

			// TODO: The Shape created here is now also an owner of the TriangleMesh object,
			// this needs to be incorp into the ObjectTable ownership logic
			rigidActor.CreateShape(triangleMeshGeom, material);

			rigidActor.GlobalPose =
				Matrix.RotationX(-(float)System.Math.PI / 2) *
				Matrix.Translation(0, 10, 0);

			scene.AddActor(rigidActor);
		}

		private void CreateConvexMesh(Scene scene, Material material)
		{
			var colladaLoader = new ColladaLoader();
			var bunny = colladaLoader.Load(@"Teapot.DAE", this.Engine.GraphicsDevice);

			var convexMeshDesc = new ConvexMeshDesc()
			{
				Flags = ConvexFlag.ComputeConvex
			};
			convexMeshDesc.SetPositions(bunny.VertexPositions);
			convexMeshDesc.SetTriangles(bunny.Indices);

			var cooking = scene.Physics.CreateCooking();

			var stream = new MemoryStream();
			bool cookResult = cooking.CookConvexMesh(convexMeshDesc, stream);

			stream.Position = 0;

			var convexMesh = scene.Physics.CreateConvexMesh(stream);

			var convexMeshGeom = new ConvexMeshGeometry(convexMesh)
			{
				Scale = new MeshScale(new Vector3(0.3f, 0.3f, 0.3f), Quaternion.Identity)
			};

			var rigidActor = scene.Physics.CreateRigidDynamic();

			// TODO: The Shape created here is now also an owner of the ConvexMesh object,
			// this needs to be incorp into the ObjectTable ownership logic
			rigidActor.CreateShape(convexMeshGeom, material);

			rigidActor.GlobalPose =
				Matrix.RotationX(-(float)System.Math.PI / 2) *
				Matrix.Translation(0, 80, 0);

			scene.AddActor(rigidActor);
		}

		private HeightFieldSample[] CreateSampleGrid(int rows, int columns)
		{
			const float height = 2;

			var samples = new HeightFieldSample[rows * columns];

			for (int r = 0; r < rows; r++)
			{
				for (int c = 0; c < columns; c++)
				{
					// Put a z and x curve together
					double h = System.Math.Sin(c) * System.Math.Cos(r) * height;

					var sample = new HeightFieldSample()
					{
						Height = (short)h
					};

					samples[r * columns + c] = sample;
				}
			}

			return samples;
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}