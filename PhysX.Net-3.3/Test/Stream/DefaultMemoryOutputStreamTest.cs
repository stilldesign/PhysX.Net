using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace PhysX.Test.Stream
{
	[TestClass]
	public class DefaultMemoryOutputStreamTest : Test
	{
		[TestMethod]
		public void InitalizeAndGetData()
		{
			using (var foundation = new Foundation())
			{
				var buffer = new byte[] { 1, 2, 3, 4, 5 };

				using (var stream = new DefaultMemoryOutputStream(buffer))
				{
					var bufferOut = stream.GetData();

					Assert.IsNotNull(bufferOut);
					Assert.AreEqual(5, bufferOut.Length);
				}
			}
		}

		[TestMethod]
		public void InitalizeWithEmptyBuffer()
		{
			using (var foundation = new Foundation())
			{
				using (var stream = new DefaultMemoryOutputStream(new byte[] { }))
				{

				}
			}
		}
	}
}