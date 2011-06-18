using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	// Copy out the dependant DLL files needed for each test run
#if x86
	[DeploymentItem(@"Assemblies\x86\PhysX3_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3Cooking_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3Gpu_x86.dll")]
#elif x64
	[DeploymentItem(@"Assemblies\x64\PhysX3_x64.dll")]
	[DeploymentItem(@"Assemblies\x64\PhysX3Cooking_x64.dll")]
	[DeploymentItem(@"Assemblies\x64\PhysX3Gpu_x64.dll")]
#endif
	[DeploymentItem(@"Assemblies\x86\PxTaskCuda.dll")]
	[TestClass]
	public abstract class Test
	{
		[TestCleanup]
		public void CleanUp()
		{
			ObjectTable.Clear();
		}

		private Physics CreatePhysics()
		{
			if (Physics.Instantiated)
				throw new Exception("Physics is still created");

			var physics = new Physics(checkRuntimeFiles: true);

			return physics;
		}
		protected PhysicsAndSceneTestUnit CreatePhysicsAndScene()
		{
			var physics = CreatePhysics();

			var scene = physics.CreateScene();

			return new PhysicsAndSceneTestUnit()
			{
				Physics = physics,
				Scene = scene
			};
		}

		protected void Update(Scene scene)
		{
			// Update Physics
			// Note: These 3 need to called together otherwise the unit test hosting process crashes
			scene.Simulate(1.0f / 60.0f);
			//this.Scene.FlushStream();
			scene.FetchResults();
		}

		protected RigidDynamic CreateBoxActor(Scene scene, float sizeX, float sizeY, float sizeZ)
		{
			return CreateBoxActor(scene, new Vector3(5, 5, 5), new Vector3(sizeX, sizeY, sizeZ));
		}
		protected RigidDynamic CreateBoxActor(Scene scene, Vector3 size, Vector3 position)
		{
			var material = scene.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

			var rigid = scene.Physics.CreateRigidDynamic();

			var shape = rigid.CreateShape(new BoxGeometry(size / 2), material);

			rigid.GlobalPose = Matrix.Translation(position);

			scene.AddActor(rigid);

			return rigid;
		}
	}
}