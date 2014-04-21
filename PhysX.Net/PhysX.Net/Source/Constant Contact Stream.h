#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public ref class ConstantContactStream
		{
			private:
				NxConstContactStream* _stream;
			
			internal:
				ConstantContactStream( NxConstContactStream* stream );
				
				property NxConstContactStream* UnmanagedPointer
				{
					NxConstContactStream* get();
				}
		};
	};
};