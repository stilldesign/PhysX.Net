#pragma once

#include <Nxp.h> 

namespace StillDesign
{
	namespace PhysX
	{
		/// <summary>128-bit Mask Used for Collision Filtering.</summary>
		public value class GroupsMask
		{
			private:
				unsigned int _bits0, _bits1, _bits2, _bits3;
			
			public:
				GroupsMask( unsigned int bits0, unsigned int bits1, unsigned int bits2, unsigned int bits3 );
				
			internal:
				static explicit operator GroupsMask( NxGroupsMask groupsMask );
				static explicit operator NxGroupsMask( GroupsMask groupsMask );
				
			public:
				property unsigned int Bits0
				{
					unsigned int get();
					void set( unsigned int value );
				}
				property unsigned int Bits1
				{
					unsigned int get();
					void set( unsigned int value );
				}
				property unsigned int Bits2
				{
					unsigned int get();
					void set( unsigned int value );
				}
				property unsigned int Bits3
				{
					unsigned int get();
					void set( unsigned int value );
				}
		};
	};
};