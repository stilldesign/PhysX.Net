using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using PhysX;

namespace PhysX.Test
{
	[TestClass]
	public class StreamExtensionsTest : Test
	{
		[TestMethod]
		public void GetData_ReturnArrayOfStructs()
		{
			var stream = new MemoryStream();

			short[] shorts = new short[50];
			for (int i = 0; i < 50; i++)
			{
				shorts[i] = (short)i;
			}

			stream.SetData(shorts);

			short[] shortsOut = stream.GetData<short>();

			for (int i = 0; i < 50; i++)
			{
				Assert.AreEqual(shorts[i], shortsOut[i]);
			}
		}
	}
}