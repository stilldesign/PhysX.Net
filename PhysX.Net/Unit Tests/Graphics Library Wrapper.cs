using System;
using System.Collections.Generic;
using System.Linq;

#if GRAPHICS_XNA2 || GRAPHICS_XNA3
using Microsoft.Xna.Framework;
#elif GRAPHICS_MDX
using Microsoft.DirectX;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

namespace StillDesign.PhysX.UnitTests
{
	public static class GraphicsLibraryWrapper
	{
		public static Matrix CreateTranslationMatrix( float x, float y, float z )
		{
			return CreateTranslationMatrix( new Vector3( x, y, z ) );
		}
		public static Matrix CreateTranslationMatrix( Vector3 translation )
		{
#if GRAPHICS_MDX || GRAPHICS_SLIMDX
			return Matrix.Translation( translation );
#elif GRAPHICS_XNA2 || GRAPHICS_XNA3
			return Matrix.CreateTranslation( translation );
#endif
		}
	}
}