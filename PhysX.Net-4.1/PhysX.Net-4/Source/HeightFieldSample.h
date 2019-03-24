#pragma once

#include "BitAndData.h"

namespace PhysX
{
	/// <summary>
	/// Heightfield sample format.
	/// </summary>
	public ref class HeightFieldSample
	{
		public:
			HeightFieldSample();

		internal:
			static PxHeightFieldSample ToUnmanaged(HeightFieldSample^ sample);
			static HeightFieldSample^ ToManaged(PxHeightFieldSample sample);

		public:
			/// <summary>
			/// The height of the heightfield sample.
			/// </summary>
			property short Height;

			/// <summary>
			/// The triangle material index of the quad's lower triangle + tesselation flag.
			/// </summary>
			property BitAndByte MaterialIndex0;

			/// <summary>
			/// The triangle material index of the quad's upper triangle + reserved flag.
			/// </summary>
			property BitAndByte MaterialIndex1;
	};
};