using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using PhysX.Math;
using PhysX.Samples.Engine.Util;

namespace PhysX.Samples.ClothSample
{
	public class ClothSample : Sample
	{
		private Cloth _flag;

		public ClothSample()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var poleActor = CreateFlagPole();

			_flag = CreateCloth(scene, poleActor);

			// Visualize the cloth
			scene.SetVisualizationParameter(VisualizationParameter.ClothVertical, true);
			scene.SetVisualizationParameter(VisualizationParameter.ClothHorizontal, true);
		}

		private Cloth CreateCloth(Scene scene, RigidActor poleActor)
		{
			// Create a grid of triangles to be our cloth
			var clothGrid = VertexGrid.CreateGrid(40, 40, 0.4f);

			// Setup the grid for cooking
			var clothMeshDesc = new ClothMeshDesc()
			{
				Points = clothGrid.Points,
				Triangles = ArrayUtil.ToByteArray(clothGrid.Indices)
			};

			// Cook
			var clothFabricStream = new MemoryStream();

			using (var cooking = scene.Physics.CreateCooking())
			{
				cooking.CookClothFabric(clothMeshDesc, new Vector3(0, -1, 0), clothFabricStream);
			}

			// Reset the seek position of the stream so we can read it form the beginning
			clothFabricStream.Position = 0;

			var clothFabric = scene.Physics.CreateClothFabric(clothFabricStream);

			var poleBoxGeom = poleActor.GetShape(0).GetBoxGeometry();
			var boxPosition = new Vector3(poleActor.GlobalPose.M41, poleActor.GlobalPose.M42, poleActor.GlobalPose.M43);

			var particles = from p in clothGrid.Points
							select new ClothParticle()
							{
								Position = p,
								// Setting the inverse weight of a particle to 0 will pin it in place, any other value will be its weight
								InverseWeight = IsPointInBox(poleBoxGeom, boxPosition, p) ? 0 : 1
							};

			// Create the cloth mesh from the cooked stream
			var cloth = scene.Physics.CreateCloth
			(
				Matrix.Translation(0, 30, 0),
				clothFabric,
				particles.ToArray(),
				(ClothFlag)0
			);

			// Enable collision with other scene geometry
			//cloth.Flags |= ClothFlag.SceneCollision;
			// GPU cloth if desired
			//cloth.Flags |= ClothFlag.GPU;

			scene.AddActor(cloth);

			return cloth;
		}
		private RigidActor CreateFlagPole()
		{
			var polePosition = new Vector3(0, 25, 0);

			// Create a flag pole to attach the cloth to
			var material = this.Scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var rigidActor = this.Scene.Physics.CreateRigidStatic();

			var boxGeom = new BoxGeometry(0.5f, 25, 0.5f);
			var boxShape = rigidActor.CreateShape(boxGeom, material);

			rigidActor.GlobalPose = Matrix.Translation(polePosition);

			this.Scene.AddActor(rigidActor);

			return rigidActor;
		}

		private bool IsPointInBox(BoxGeometry box, Vector3 boxPosition, Vector3 point)
		{
			Vector3 min = boxPosition - box.HalfExtents;
			Vector3 max = boxPosition + box.HalfExtents;

			bool outside =
				point.X < min.X || point.X > max.X ||
				point.Y < min.Y || point.Y > max.Y ||
				point.Z < min.Z || point.Z > max.Z;

			return !outside;
		}

		protected override void Update(TimeSpan elapsed)
		{
			// Set some wind in a random direction every 3 seconds
			if ((int)elapsed.TotalSeconds % 3 == 0)
			{
				var r = new Random();

				double x = 25 + r.NextDouble() * 15;
				double y = -5 + r.NextDouble() * 10;
				double z = -5 + r.NextDouble() * 10;

				_flag.ExternalAcceleration = new Vector3((float)x, (float)y, (float)z);
			}
		}

		protected override void Draw()
		{

		}
	}
}