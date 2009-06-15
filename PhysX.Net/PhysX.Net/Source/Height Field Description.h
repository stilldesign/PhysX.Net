#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "Height Field Sample.h"

namespace StillDesign
{
	namespace PhysX
	{
		public ref class HeightFieldDescription
		{
			private:
				NxHeightFieldDesc* _heightFieldDesc;
				
				array<HeightFieldSample>^ _samples;
				
			public:
				HeightFieldDescription();
				!HeightFieldDescription();
			protected:
				~HeightFieldDescription();
				
			public:
				/// <summary>Resets the structure to the default</summary>
				void SetToDefault();
				/// <summary>Returns true if the descriptor is valid</summary>
				bool IsValid();
				
				void SetSamples( array<HeightFieldSample>^ value );
				
				/// <summary>Gets or Sets the number of sample rows in the height field samples array</summary>
				property int NumberOfRows
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the number of sample columns in the height field samples array</summary>
				property int NumberOfColumns
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the format of the sample data</summary>
				property HeightFieldFormat Format
				{
					HeightFieldFormat get();
					void set( HeightFieldFormat value );
				}
				
				/// <summary>Gets or Sets the samples array</summary>
				property array<HeightFieldSample>^ Samples
				{
					array<HeightFieldSample>^ get();
				}
				/// <summary>Gets the offset in bytes between consecutive samples in the samples array</summary>
				property int SampleStrideSize
				{
					int get();
				}
				
				/// <summary>Gets or Sets how thick the heightfield surface is</summary>
				property float Thickness
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float ConvexEdgeThreshold
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property HeightFieldFlag Flags
				{
					HeightFieldFlag get();
					void set( HeightFieldFlag flags );
				}
				
				/// <summary>Gets or Sets how far 'below ground' the height volume extends (Deprecated)</summary>
				property float VerticalExtent
				{
					float get();
					void set( float value );
				}
				
			internal:
				property NxHeightFieldDesc* UnmanagedPointer
				{
					NxHeightFieldDesc* get();
				}
		};
	};
};