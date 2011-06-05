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
		}

		private Deformable CreateCloth(Scene scene)
		{
			var clothGrid = new VertexGrid(25, 25);

			var deformableMeshDesc = new DeformableMeshDesc()
			{
				NumberOfPrimitives = clothGrid.Indices.Length / 3,
				NumberOfVertices = clothGrid.Points.Length,
				PrimitiveType = DeformablePrimitiveType.Triangle,
				Vertices = clothGrid.Points
			};
			deformableMeshDesc.SetPrimitives(clothGrid.Indices);

			var deformableMeshStream = new MemoryStream();

			var cooking = scene.Physics.CreateCooking();

			bool result = cooking.CookDeformableMesh(deformableMeshDesc, deformableMeshStream);

			deformableMeshStream.Position = 0;

			var deformableMesh = scene.Physics.CreateDeformableMesh(deformableMeshStream);

			var desc = new DeformableDesc()
			{
				DeformableMesh = deformableMesh,
				Flags = ActorFlag.Visualization,
				Mass = 10,
				GlobalPose = Matrix.Translation(0, 5, 0),
				BendingStiffness = 0.1f,
				StretchingStiffness = 0.1f,
				DeformableFlags = DeformableFlag.Bending
			};

			var deformable = scene.Physics.CreateDeformable(desc);

			scene.AddActor(deformable);

			//

			scene.SetVisualizationParameter(VisualizationParameter.DeformableMesh, true);

			return deformable;
		}
		private void CreateFlagPole(Deformable cloth)
		{
			// Create a flag pole to attach the cloth to
			var material = this.Scene.Physics.CreateMaterial(0.1f, 0.1f, 0.1f);

			var rigidActor = this.Scene.Physics.CreateRigidDynamic();

			var boxGeom = new BoxGeometry(2, 30, 2);
			var boxShape = rigidActor.CreateShape(boxGeom, material);

			rigidActor.GlobalPose = Matrix.Translation(0, 15, 0);
			rigidActor.SetMassAndUpdateInertia(10);
			rigidActor.Flags = RigidDynamicFlags.Kinematic;

			this.Scene.AddActor(rigidActor);

			// Attach the cloth
			var clothGrid = new VertexGrid(25, 25);
			var attachment = this.Scene.Physics.CreateAttachment(cloth, boxShape, clothGrid.Indices, clothGrid.Points, Enumerable.Range(0, clothGrid.Points.Length).ToArray());
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}