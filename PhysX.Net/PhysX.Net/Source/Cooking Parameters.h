#pragma once

#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		public value class CookingParameters
		{
			internal:
				static NxCookingParams ToUnmanaged( CookingParameters parameters );
				static CookingParameters ToManaged( NxCookingParams parameters );
			
			public:	
				/// <summary>Hint to choose speed or less memory for collision structures.</summary>
				property StillDesign::PhysX::Platform Platform;

				/// <summary>Skin width for convexes.</summary>
				property float SkinWidth;

				/// <summary>Target platform.</summary>
				property CookingResourceType ResourceType;
		};
	};
};