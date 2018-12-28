#pragma once

#include "HeightFieldEnum.h"
#include "HeightFieldSample.h"

namespace PhysX
{
	public ref class HeightFieldDesc
	{
		internal:
			static PxHeightFieldDesc ToUnmanaged(HeightFieldDesc^ desc);

		public:
			HeightFieldDesc();

			bool IsValid();
			void SetToDefault();

			/// <summary>
			/// Number of sample rows in the height field samples array.
			/// </summary>
			property int NumberOfRows;

			/// <summary>
			/// Number of sample columns in the height field samples array.
			/// </summary>
			property int NumberOfColumns;

			/// <summary>
			/// Format of the sample data.
			/// </summary>
			property HeightFieldFormat Format;
			
			/// <summary>
			/// The samples array.
			/// </summary>
			property array<HeightFieldSample^>^ Samples;

			/// <summary>
			/// Gets or sets how thick the heightfield surface is. 
			/// </summary>
			property float Thickness;

			/// <summary>
			/// 
			/// </summary>
			property float ConvexEdgeThreshold;

			/// <summary>
			/// Gets or sets Flags bits, combined from values of the enum PxHeightFieldFlag.  
			/// </summary>
			property HeightFieldFlag Flags;
	};
};