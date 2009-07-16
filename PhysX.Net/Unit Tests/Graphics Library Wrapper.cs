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

		public static Matrix CreateRotationX( float angle )
		{
#if GRAPHICS_MDX || GRAPHICS_SLIMDX
			return Matrix.RotationX( angle );
#elif GRAPHICS_XNA2 || GRAPHICS_XNA3
			return Matrix.CreateRotationX( angle );
#endif
		}
		public static Matrix CreateRotationY( float angle )
		{
#if GRAPHICS_MDX || GRAPHICS_SLIMDX
			return Matrix.RotationY( angle );
#elif GRAPHICS_XNA2 || GRAPHICS_XNA3
			return Matrix.CreateRotationY( angle );
#endif
		}
		public static Matrix CreateRotationZ( float angle )
		{
#if GRAPHICS_MDX || GRAPHICS_SLIMDX
			return Matrix.RotationZ( angle );
#elif GRAPHICS_XNA2 || GRAPHICS_XNA3
			return Matrix.CreateRotationZ( angle );
#endif
		}

		public static Vector3 Vector3Empty
		{
			get
			{
				return new Vector3( 0, 0, 0 );
			}
		}
	}
}