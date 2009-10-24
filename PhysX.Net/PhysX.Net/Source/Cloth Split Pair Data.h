#pragma once

#include "Cloth Split Pair.h"

class NxClothSplitPairData;

namespace StillDesign
{
	namespace PhysX
	{
		/// <summary>User-side class for receiving triangle split events for torn cloth.</summary>
		public ref class ClothSplitPairData
		{
			private:
				NxClothSplitPairData* _data;
			
			internal:
				ClothSplitPairData( NxClothSplitPairData* splitPairData );
			protected:
				~ClothSplitPairData();
			public:
				!ClothSplitPairData();
				
				array<ClothSplitPair>^ GetSplitPairs();
				
				property int MaximumSplitPairs
				{
					int get();
					void set( int value );
				}
				property int NumberOfSplitPairs
				{
					int get();
				}
		};
	};
};