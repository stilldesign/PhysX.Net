#pragma once

#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		public value class CookingParameters
		{
			private:
				StillDesign::PhysX::Platform _platform;
				CookingResourceType _resourceType;
				float _skinWidth;
			
			internal:
				static explicit operator NxCookingParams( CookingParameters parameters );
				static explicit operator CookingParameters( NxCookingParams parameters );
			
			public:	
				/// <summary></summary>
				property StillDesign::PhysX::Platform Platform
				{
					StillDesign::PhysX::Platform get();
					void set( StillDesign::PhysX::Platform value );
				}
				/// <summary></summary>
				property float SkinWidth
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property CookingResourceType ResourceType
				{
					CookingResourceType get();
					void set( CookingResourceType value );
				}
		};
	};
};