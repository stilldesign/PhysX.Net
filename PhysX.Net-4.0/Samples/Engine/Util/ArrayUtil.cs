using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PhysX.Samples.Engine.Util
{
	public static class ArrayUtil
	{
		public static byte[] ToByteArray(int[] array)
		{
			byte[] bytes = new byte[sizeof(int) * array.Length];

			for (int i = 0; i < array.Length; i++)
			{
				byte[] k = BitConverter.GetBytes(array[i]);

				for (int j = 0; j < k.Length; j++)
				{
					bytes[i * sizeof(int) + j] = k[j];
				}
			}

			return bytes;
		}

		//public static byte[] ToByteArray<T>(T[] array)
		//	where T : struct
		//{
		//	int t = Marshal.SizeOf(typeof(T));

		//	GCHandle pinSrc = GCHandle.Alloc(array[0], GCHandleType.Pinned);

		//	var bytes = new byte[t * array.Length];

		//	Marshal.Copy(pinSrc.AddrOfPinnedObject(), bytes, 0, t * array.Length);

		//	pinSrc.Free();

		//	return bytes;
		//}
	}
}