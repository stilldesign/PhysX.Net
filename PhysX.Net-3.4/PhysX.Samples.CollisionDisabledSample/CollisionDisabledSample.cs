using System;
using System.Numerics;

namespace PhysX.Samples.CollisionDisabledSample
{
	public class CollisionDisabledSample : Sample
	{
		private Scene _scene;
		private Material _material;

		public CollisionDisabledSample()
			: base(SetupFilters)
		{
			Run();
		}

		private static void SetupFilters(SceneDesc sceneDesc)
		{
			sceneDesc.SimulationFilterCallback = new CollisionDisabledSimulationFilterCallback();
			sceneDesc.FilterShader = new CollisionDisabledFilterShader();
		}

		protected override void LoadContent()
		{

		}

		protected override void LoadPhysics(Scene scene)
		{
			_scene = scene;
			_material = scene.Physics.CreateMaterial(0.7f, 0.7f, 0.1f);

			// Create some boxes that are above each other
			var a = CreateBox(new Vector3(0, 10, 0));
			var b = CreateBox(new Vector3(0, 20, 0));
			var c = CreateBox(new Vector3(0, 30, 0));

			// Pass boxes B and C to our filter callback
			var filter = scene.FilterCallback as CollisionDisabledSimulationFilterCallback;
			filter.DisableCollisionBetweenActors.Add(new Tuple<RigidActor, RigidActor>(b, c));
		}

		private RigidDynamic CreateBox(Vector3 position)
		{
			var actor = _scene.Physics.CreateRigidDynamic();

			var boxGeom = new BoxGeometry(2, 2, 2);
			var boxShape = actor.CreateShape(boxGeom, _material);

			actor.GlobalPose = Matrix4x4.CreateTranslation(position);
			actor.SetMassAndUpdateInertia(10);

			_scene.AddActor(actor);

			return actor;
		}

		protected override void Update(TimeSpan elapsed)
		{

		}

		protected override void Draw()
		{

		}
	}
}