#pragma once

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		public value class HeightFieldSample
		{
			private:
				short _height;
				Byte _materialIndex0;
				Byte _materialIndex1;
				Byte _tessFlag;
				
			internal:
				static HeightFieldSample FromUnmanaged( NxHeightFieldSample* sample );
				static NxHeightFieldSample ToUnmanaged( HeightFieldSample sample );
				
			public:
				property short Height
				{
					short get();
					void set( short value );
				}
				property Byte MaterialIndex0
				{
					Byte get();
					void set( Byte value );
				}
				property Byte MaterialIndex1
				{
					Byte get();
					void set( Byte value );
				}
				property Byte TessellationFlag
				{
					Byte get();
					void set( Byte value );
				}
		};
	};
};