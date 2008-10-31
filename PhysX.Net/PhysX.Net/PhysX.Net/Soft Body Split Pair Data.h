#pragma once

#include "Soft Body Split Pair.h"

namespace StillDesign
{
	namespace PhysX
	{
		public ref class SoftBodySplitPairData
		{
			private:
				NxSoftBodySplitPairData* _data;
			
				array<SoftBodySplitPair>^ _pairs;
				
			public:
				SoftBodySplitPairData();
			internal:
				SoftBodySplitPairData( NxSoftBodySplitPairData data );
			public:
				~SoftBodySplitPairData();
			protected:
				!SoftBodySplitPairData();
				
			public:
				void SetToDefault();
				bool IsValid();
				
				property array<SoftBodySplitPair>^ SplitPairs
				{
					array<SoftBodySplitPair>^ get();
				}
		};
	};
};