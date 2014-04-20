#pragma once

class NxClothSplitPairData;

namespace StillDesign
{
	namespace PhysX
	{
		public value class ClothSplitPair
		{
			public:
				static ClothSplitPair FromUnmanaged( NxClothSplitPair pair );
				
				property int TriangleIndex0;
				property int TriangleIndex1;
				property Byte EdgeIndex0;
				property Byte EdgeIndex1;
		};
	};
};