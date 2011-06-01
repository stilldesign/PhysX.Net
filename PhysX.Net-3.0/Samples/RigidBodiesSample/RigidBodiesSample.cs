using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using PhysX.Samples;
using PhysX.Math;

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
			for (int i = 0; i < 10; i++)
			{
				var rigidActor = scene.Physics.CreateRigidDynamic();

				var boxGeom = new BoxGeometry(2, 2, 2);
				var boxShape = rigidActor.CreateShape(boxGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(-20, 10 + i * (boxGeom.Size.Y + 0.5f), 0);
				rigidActor.SetMassAndUpdateInertia(10);

				scene.AddActor(rigidActor);
			}

			// Spheres
			for (int i = 0; i < 10; i++)
			{
				var rigidActor = scene.Physics.CreateRigidDynamic();

				var sphereGeom = new SphereGeometry(radius: 2);
				var boxShape = rigidActor.CreateShape(sphereGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(-10, 10 + i * (sphereGeom.Radius * 2 + 0.5f), 0);
				rigidActor.SetMassAndUpdateInertia(10);

				scene.AddActor(rigidActor);
			}

			// Capsule
			for (int i = 0; i < 10; i++)
			{
				var rigidActor = scene.Physics.CreateRigidDynamic();

				var capsuleGeom = new CapsuleGeometry(radius: 2, halfHeight: 2);
				var boxShape = rigidActor.CreateShape(capsuleGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(0, 10 + i * (capsuleGeom.HalfHeight + capsuleGeom.Radius + 0.5f), 0);
				rigidActor.SetMassAndUpdateInertia(10);

				scene.AddActor(rigidActor);
			}

			// HeightField
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

				var heightFieldGeom = new HeightFieldGeometry(heightField, MeshGeometryFlag.SmoothSphereCollisions, 1, scale, scale);

				rigidActor.CreateShape(heightFieldGeom, material);

				rigidActor.GlobalPose = Matrix.Translation(30, 10, -32.5f);

				scene.AddActor(rigidActor);
			}
		}

		private static HeightFieldSample[] CreateSampleGrid(int rows, int columns)
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