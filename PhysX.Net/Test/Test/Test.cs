using System;
using System.Diagnostics;
using System.Numerics;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test
{
	[TestClass]
	[DeploymentItem("PhysX_64.dll")]
	[DeploymentItem("PhysXCommon_64.dll")]
	[DeploymentItem("PhysXCooking_64.dll")]
	[DeploymentItem("PhysXDevice64.dll")]
	[DeploymentItem("PhysXFoundation_64.dll")]
	[DeploymentItem("PhysXGpu_64.dll")]
	public abstract class Test
	{
		private ErrorLog _errorLog;

		private static PhysX.Foundation _foundation;
		private static PhysX.Physics _physics;

		[TestCleanup]
		public void CleanUp()
		{
			if (Physics.Instantiated)
			{
				_foundation?.Dispose();
				_foundation = null;

				throw new Exception("After a test has run, the Physics singleton should have been disposed");
			}

			ObjectTable.Instance.Clear();

			if (_errorLog != null && _errorLog.HasErrors)
			{
				Trace.TraceError("There were errors, check the error log");
			}

			_errorLog = null;
		}

		[TestInitialize]
		public void TestInitialize()
		{
			if (Physics.Instantiated)
				throw new Exception("Before a test run, the Physics singleton should not be initalized. Probably spill over from a previous test.");
		}

		protected Physics CreatePhysics(ErrorCallback errorCallback = null)
		{
			if (Physics.Instantiated)
				Assert.Fail("Physics is still created");

			if (errorCallback == null)
				errorCallback = _errorLog = new ErrorLog();

			if (_physics != null)
			{
				_physics.Dispose();
				_physics = null;
			}
			if (_foundation != null)
			{
				_foundation.Dispose();
				_foundation = null;
			}

			_foundation = new Foundation(errorCallback);

			_physics = new Physics(_foundation, checkRuntimeFiles: true);

			return _physics;
		}
		protected PhysicsAndSceneTestUnit CreatePhysicsAndScene()
		{
			_errorLog = new ErrorLog();

			var physics = CreatePhysics(_errorLog);

			var scene = physics.CreateScene();

			return new PhysicsAndSceneTestUnit()
			{
				Foundation = physics.Foundation,
				Physics = scene.Physics,
				Scene = scene,
				ErrorOutput = _errorLog
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

			rigid.GlobalPose = Matrix4x4.CreateTranslation(position);

			scene.AddActor(rigid);

			return rigid;
		}

		protected void AssertNoPhysXErrors(PhysicsAndSceneTestUnit physics)
		{
			Assert.IsFalse(physics.ErrorOutput.HasErrors, physics.ErrorOutput.LastError);
		}
	}
}