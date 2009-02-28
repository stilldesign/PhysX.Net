using System;
using System.Collections.Generic;

namespace StillDesign
{
	public static class Mathematics
	{
		public static float Clamp( float value, float max, float min )
		{
			if( value < min )
				return min;
			if( value > max )
				return max;

			return value;
		}
	}
}