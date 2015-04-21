using System;
using SharpDX;

namespace PhysX.Samples
{
	public static class ViewportExtensions
	{
		public static float AspectRatio(this Viewport viewport)
		{
			return (float)viewport.Width / (float)viewport.Height;
		}
	}
}