#pragma once

#include "Soft Body Split Pair.h"
#include "BufferData.h"
#include "Physics Stream.h"

UsingFrameworkNamespace
using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class SoftBodySplitPairData : BufferData, IDisposable, ICloneable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

			private:
				NxSoftBodySplitPairData* _data;
				
				PhysicsStream^ _splitPairs;

			public:
				SoftBodySplitPairData();
				~SoftBodySplitPairData();
			protected:
				!SoftBodySplitPairData();
			
			internal:
				static SoftBodySplitPairData^ FromUnmanaged( NxSoftBodySplitPairData* data, bool objectOwner, bool dataOwner );

			public:
				property bool IsDisposed
				{
					virtual bool get();
				}

				virtual SoftBodySplitPairData^ Clone();
				virtual Object^ ICloneableClone() = ICloneable::Clone;

				void AllocateSplitPairs( int count );

				void SetToDefault();
				bool IsValid();
				int CheckValid();
				
				array<SoftBodySplitPair>^ GetSplitPairs();

				property Nullable<int> MaximumSplitPairs
				{
					Nullable<int> get();
					void set( Nullable<int> value );
				}

				property int SplitPairsByteStride
				{
					int get()
					{
						return sizeof(NxSoftBodySplitPair);
					}
				}

				property NxSoftBodySplitPairData* UnmanagedPointer
				{
					NxSoftBodySplitPairData* get();
				}
		};
	};
};