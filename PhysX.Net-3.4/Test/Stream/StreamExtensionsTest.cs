using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
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
			unsafe
			{
				short[] @in = new short[50];
				for (int i = 0; i < 50; i++)
				{
					@in[i] = (short)i;
				}

				int inSize = 100; // 50 x 2 bytes per short

				// Allocate a block of unmanaged memory and return an IntPtr object.	
				IntPtr memIntPtr = Marshal.AllocHGlobal(inSize);

				// Get a byte pointer from the IntPtr object. 
				byte* memBytePtr = (byte*)memIntPtr.ToPointer();

				var stream = new UnmanagedMemoryStream(memBytePtr, inSize);

				// Set the data
				stream.SetData(@in);

				// Get the data back out
				short[] @out = stream.GetData<short>();

				Assert.AreEqual(@in.Length, @out.Length);

				for (int i = 0; i < 50; i++)
				{
					Assert.AreEqual(@in[i], @out[i]);
				}
			}
		}
	}
}