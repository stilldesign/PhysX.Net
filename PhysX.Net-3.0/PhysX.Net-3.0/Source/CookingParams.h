#pragma once

#include "CookingEnum.h"
#include <PxCooking.h> 

namespace PhysX
{
	/// <summary>
	/// Structure describing parameters affecting mesh cooking.
	/// </summary>
	public ref class CookingParams
	{
		internal:
			static PxCookingParams ToUnmanaged(CookingParams^ params);
			static CookingParams^ ToManaged(PxCookingParams params);

		public:
			property Platform TargetPlatform;

			property float SkinWidth;

			property bool SuppressTriangleMeshRemapTable;
	};
};