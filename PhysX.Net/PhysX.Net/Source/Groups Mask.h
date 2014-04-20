#pragma once

#include <Nxp.h> 

namespace StillDesign
{
	namespace PhysX
	{
		/// <summary>128-bit mask used for collision filtering.</summary>
		public value class GroupsMask
		{
			public:
				GroupsMask( unsigned int bits0, unsigned int bits1, unsigned int bits2, unsigned int bits3 );
				
			internal:
				static explicit operator GroupsMask( NxGroupsMask groupsMask );
				static explicit operator NxGroupsMask( GroupsMask groupsMask );
				
			public:
				property unsigned int Bits0;
				property unsigned int Bits1;
				property unsigned int Bits2;
				property unsigned int Bits3;
		};
	};
};