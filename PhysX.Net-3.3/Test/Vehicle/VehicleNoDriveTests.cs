using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Vehicle
{
	[TestClass]
	public class VehicleNoDriveTests : Test
	{
		private PhysicsAndSceneTestUnit _physics;
		private VehicleNoDrive _noDrive;

		[TestInitialize]
		public void TestInitalize()
		{
			_physics = CreatePhysicsAndScene();


			var actor = CreateBoxActor(_physics.Scene, 5, 5, 5);

			var simData = new VehicleWheelsSimData(4)
			{

			};

			_noDrive = new VehicleNoDrive(_physics.Physics, actor, simData);

		}
		[TestCleanup]
		public void TestCleanup()
		{
			_noDrive.Dispose();
			_physics.Dispose();
		}

		[TestMethod]
		public void ConstructAndDispose()
		{

		}

		[TestMethod]
		public void BrakeTorque()
		{
			_noDrive.SetBrakeTorque(0, 42);

			Assert.AreEqual(42, _noDrive.GetBrakeTorque(0));
		}

		[TestMethod]
		public void SettingBrakeTorqueOf5thOf4Wheels()
		{
			// PhysX noops this
			_noDrive.SetBrakeTorque(5, 66);
		}

		[TestMethod]
		public void GetttingBrakeTorqueOf5thOf4Wheels()
		{
			// PhysX noops this and outputs a warning, but it atleast doesn't exception
			_noDrive.GetBrakeTorque(5);
		}
	}
}