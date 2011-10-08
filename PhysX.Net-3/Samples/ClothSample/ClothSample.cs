using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using PhysX.Math;

namespace PhysX.Samples.ClothSample
{
	public class ClothSample : Sample
	{
		public ClothSample()
		{
			Run();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			var cloth = CreateCloth(scene);

			CreateFlagPole(cloth);

			// Visualize the cloth
			scene.SetVisualizationParameter(VisualizationParameter.DeformableMesh, true);
		}

		private Deformable CreateCloth(Scene scene)
		{
			// Create a grid of triangles to be our cloth
			var clothGrid = new VertexGrid(25, 25);

			// Setup the grid for cooking
			var deformableMeshDesc = new DeformableMeshDesc()
			{
				// Clothes are made up of triangles. There are 3 indices per triangle.
				NumberOfPrimitives = clothGrid.Indices.Length / 3,
				NumberOfVertices = clothGrid.Points.Length,
				PrimitiveType = DeformablePrimitiveType.Triangle,
				Vertices = clothGrid.Points,
				Primitives = clothGrid.Indices
			};

			// Cook
			var deformableMeshStream = new MemoryStream();

			using (var cooking = scene.Physics.CreateCooking())
			{
				bool result = cooking.CookDeformableMesh(deformableMeshDesc, deformableMeshStream);

				if (!result)
					throw new Exception("Failed to cook deformable mesh");
			}

			// Reset the seek position of the stream so we can read it form the beginning
			deformableMeshStream.Position = 0;

			// Create the deformable mesh from the cooked stream
			var deformableMesh = scene.Physics.CreateDeformableMesh(deformableMeshStream);

			// Create the deformable object using the above mesh
			// Set the bending amount to a low value to make it act like cloth, 
			// but set the strectching amount to a high value to stop it looking like rubber,
			// finally add some wind to make it flap around like a flag.
			var desc = new DeformableDesc()
			{
				DeformableMesh = deformableMesh,
				Flags = ActorFlag.Visualization,
				Mass = 10,
				GlobalPose = Matrix.Translation(0, 5, 0),
				BendingStiffness = 0.15f,
				StretchingStiffness = 0.95f,
				DeformableFlags = DeformableFlag.Bending,
				WindAcceleration = new Vector3(60, 0.01f, 0)
			};

			var deformable = scene.Physics.CreateDeformable(desc);

			scene.AddActor(deformable);

			return deformable;
		}
		private void CreateFlagPole(Deformable cloth)
		{
			var polePosition = new Vector3(0, 30, 0);

			// Create a flag pole to attach the cloth to
			var material = this.Scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var rigidActor = this.Scene.Physics.CreateRigidStatic();

			var boxGeom = new BoxGeometry(2, 30, 2);
			var boxShape = rigidActor.CreateShape(boxGeom, material);

			rigidActor.GlobalPose = Matrix.Translation(polePosition);
			//rigidActor.SetMassAndUpdateInertia(10);
			//rigidActor.Flags = RigidDynamicFlags.Kinematic;

			this.Scene.AddActor(rigidActor);

			// Attach the cloth
			var clothGrid = new VertexGrid(25, 25);

			// TODO: Clean up the below code
			// I'd like this to use the FindPointsInsideBoxGeom method instead (more generic)
			Vector3[] p;
			int[] i;
			FindPointsInsideBoxGeom(boxGeom, polePosition, clothGrid, out p, out i);

			p = clothGrid.Points.Take(75).ToArray();
			i = Enumerable.Range(0, 75).ToArray();
			var f = new int[p.Length];

			var attachment = this.Scene.Physics.CreateAttachment(cloth, boxShape, i, p, f);
		}

		private void FindPointsInsideBoxGeom(BoxGeometry box, Vector3 boxPosition, VertexGrid grid, out Vector3[] points, out int[] indices)
		{
			var i = new List<Vector3>();
			var j = new List<int>();

			foreach (int index in grid.Indices)
			{
				Vector3 p = grid.Points[index] + new Vector3(0, 5, 0);

				if (IsPointInBox(box, boxPosition, p))
				{
					i.Add(p);
					j.Add(index);
				}
			}

			points = i.ToArray();
			indices = j.ToArray();
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

		}

		protected override void Draw()
		{

		}
	}
}