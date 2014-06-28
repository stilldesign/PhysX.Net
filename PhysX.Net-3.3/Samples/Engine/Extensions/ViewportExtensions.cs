using System;
using System.Collections.Generic;
using System.Linq;
using SlimDX.Direct3D11;

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