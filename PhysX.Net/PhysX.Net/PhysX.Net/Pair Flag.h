#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		
		public ref class PairFlag
		{
			private:
				Object^ _objectA;
				Object^ _objectB;
				
				unsigned int _flags;
				
			public:
				PairFlag();
				PairFlag( Object^ objectA, Object^ objectB, unsigned int flags );
			internal:
				PairFlag( NxPairFlag pairFlag );
				
			public:
				property Object^ ObjectA
				{
					Object^ get();
				}
				property Object^ ObjectB
				{
					Object^ get();
				}
				
				property unsigned int Flags
				{
					unsigned int get();
				}
		};
	};
};