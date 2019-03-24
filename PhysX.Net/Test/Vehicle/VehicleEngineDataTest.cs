using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Vehicle
{
	[TestClass]
	public class VehicleEngineDataTest : Test
	{
		[TestMethod]
		public void ManagedUnmanagedConversion()
		{
			var engineData = new VehicleEngineData()
			{
				DampingRateFullThrottle = 1,
				DampingRateZeroThrottleClutchDisengaged = 2,
				DampingRateZeroThrottleClutchEngaged = 3,
				MaxOmega = 4,
				PeakTorque = 5
			};

			var conversion = VehicleEngineData.TestManagedUnmanagedConversion(engineData);

			Assert.AreEqual(1, conversion.DampingRateFullThrottle);
			Assert.AreEqual(2, conversion.DampingRateZeroThrottleClutchDisengaged);
			Assert.AreEqual(3, conversion.DampingRateZeroThrottleClutchEngaged);
			Assert.AreEqual(4, conversion.MaxOmega);
			Assert.AreEqual(5, conversion.PeakTorque);
		}
	}
}