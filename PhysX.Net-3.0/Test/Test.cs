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
			this.Scene = null;
			this.Physics = null;

			ObjectTable.Clear();
		}

		protected Physics CreatePhysics()
		{
			if (this.Physics != null || PhysX.Physics.Instantiated)
				throw new Exception("Physics is still created");

			this.Physics = new Physics(checkRuntimeFiles: true);
			this.Physics.OnDisposed += Physics_OnDisposed;

			return this.Physics;
		}
		protected Scene CreatePhysicsAndScene()
		{
			CreatePhysics();

			this.Scene = this.Physics.CreateScene();

			return this.Scene;
		}

		void Physics_OnDisposed(object sender, EventArgs e)
		{
			this.Physics = this.Physics = null;

			this.Scene = null;
		}

		protected void Update()
		{
			// Update Physics
			// Note: These 3 need to called together otherwise the unit test hosting process crashes
			this.Scene.Simulate(1.0f / 60.0f);
			//this.Scene.FlushStream();
			this.Scene.FetchResults();
		}

		protected RigidDynamic CreateBoxActor(float sizeX, float sizeY, float sizeZ, string name = "Box")
		{
			return CreateBoxActor(new Vector3(5, 5, 5), new Vector3(sizeX, sizeY, sizeZ));
		}
		protected RigidDynamic CreateBoxActor(Vector3 size, Vector3 position)
		{
			var material = this.Physics.CreateMaterial(0.5f, 0.5f, 0.1f);

			var rigid = this.Physics.CreateRigidDynamic();

			var shape = rigid.CreateShape(new BoxGeometry(size / 2), material);

			rigid.GlobalPose = Matrix.Translation(position);

			this.Scene.AddActor(rigid);

			return rigid;
		}

		//

		protected Physics Physics { get; private set; }
		protected Scene Scene { get; private set; }
	}
}