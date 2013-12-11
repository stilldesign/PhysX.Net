using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
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

			//CreateFlagPole(cloth);

			// Visualize the cloth
			//scene.SetVisualizationParameter(VisualizationParameter.cloth, true);
		}

		// TODO: Move later
		public static class ArrayUtil
		{
			public static byte[] ToByteArray<T>(T[] array)
				where T : struct
			{
				int t = Marshal.SizeOf(typeof(T));

				GCHandle pinSrc = GCHandle.Alloc(array, GCHandleType.Pinned);

				var bytes = new byte[t * array.Length];

				Marshal.Copy(pinSrc.AddrOfPinnedObject(), bytes, 0, t * array.Length);

				pinSrc.Free();

				return bytes;
			}
		}

		private Cloth CreateCloth(Scene scene)
		{
			// Create a grid of triangles to be our cloth
			var clothGrid = new VertexGrid(25, 25);

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

			var particles = from p in clothGrid.Points
							select new ClothParticle()
							{
								Position = p,
								InverseWeight = 0.1f
							};

			// Create the cloth mesh from the cooked stream
			var cloth = scene.Physics.CreateCloth(
				Matrix.Identity,
				clothFabric,
				particles.ToArray(),
				0);

			scene.AddActor(cloth);

			return cloth;
		}
		//private void CreateFlagPole(Cloth cloth)
		//{
		//    var polePosition = new Vector3(0, 30, 0);

		//    // Create a flag pole to attach the cloth to
		//    var material = this.Scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

		//    var rigidActor = this.Scene.Physics.CreateRigidStatic();

		//    var boxGeom = new BoxGeometry(2, 30, 2);
		//    var boxShape = rigidActor.CreateShape(boxGeom, material);

		//    rigidActor.GlobalPose = Matrix.Translation(polePosition);
		//    //rigidActor.SetMassAndUpdateInertia(10);
		//    //rigidActor.Flags = RigidDynamicFlags.Kinematic;

		//    this.Scene.AddActor(rigidActor);

		//    // Attach the cloth
		//    var clothGrid = new VertexGrid(25, 25);

		//    // TODO: Clean up the below code
		//    // I'd like this to use the FindPointsInsideBoxGeom method instead (more generic)
		//    Vector3[] p;
		//    int[] i;
		//    FindPointsInsideBoxGeom(boxGeom, polePosition, clothGrid, out p, out i);

		//    p = clothGrid.Points.Take(75).ToArray();
		//    i = Enumerable.Range(0, 75).ToArray();
		//    var f = new int[p.Length];

		//    var attachment = this.Scene.Physics.CreateAttachment(cloth, boxShape, i, p, f);
		//}

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