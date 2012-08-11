using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX.Math;

namespace PhysX.Test
{
	// Copy out the dependant DLL files needed for each test run
#if x86
	[DeploymentItem(@"Assemblies\x86\PhysX3CharacterKinematicCHECKED_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3CHECKED_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3CommonCHECKED_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3CookingCHECKED_x86.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3GpuCHECKED_x86.dll")]
#elif x64
	[DeploymentItem(@"Assemblies\x86\PhysX3CharacterKinematicCHECKED_x64.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3CHECKED_x64.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3CommonCHECKED_x64.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3CookingCHECKED_x64.dll")]
	[DeploymentItem(@"Assemblies\x86\PhysX3GpuCHECKED_x64.dll")]
#endif
	[TestClass]
	public abstract class Test
	{
		[TestCleanup]
		public void CleanUp()
		{
			ObjectTable.Clear();
		}

		private Physics CreatePhysics(ErrorCallback errorCallback = null)
		{
			if (Physics.Instantiated)
				Assert.Fail("Physics is still created");

			var foundation = new Foundation(errorCallback);

			var physics = new Physics(foundation, checkRuntimeFiles: true);

			return physics;
		}
		protected PhysicsAndSceneTestUnit CreatePhysicsAndScene()
		{
			var errors = new ErrorLog();

			var physics = CreatePhysics(errors);

			var scene = physics.CreateScene();

			return new PhysicsAndSceneTestUnit()
			{
				Foundation = physics.Foundation,
				Physics = scene.Physics,
				Scene = scene,
				ErrorOutput = errors
			};
		}

		protected RigidDynamic CreateBoxActor(Scene scene, float x, float y, float z)
		{
			return CreateBoxActor(scene, new Vector3(5, 5, 5), new Vector3(x, y, z));
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

		protected void AssertNoPhysXErrors(PhysicsAndSceneTestUnit physics)
		{
			Assert.IsFalse(physics.ErrorOutput.HasErrors, physics.ErrorOutput.LastError);
		}
	}
}