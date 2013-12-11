using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;

namespace PhysX.Test.Util
{
	public static class ArrayUtil
	{
		public static byte[] ToByteArray<T>(T[] array)
			where T : struct
		{
			int t = Marshal.SizeOf(typeof(T));

			GCHandle pinSrc = GCHandle.Alloc(array, GCHandleType.Pinned);

			var bytes = new byte[t * array.Length];

			Marshal.Copy(pinSrc.AddrOfPinnedObject(), bytes, 0, t * array.Length);

			pinSrc.Free();

			return bytes;
		}
	}
}