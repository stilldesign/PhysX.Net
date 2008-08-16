#pragma once

#include <NxSpringDesc.h>

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		/// <summary>Describes a joint spring</summary>
		public value class SpringDescription
		{
			private:
				float _spring;
				float _damper;
				float _targetValue;
				
			public:
				SpringDescription( float springCoefficient, float damperCoefficient, float targetValue );
				
			internal:
				static explicit operator NxSpringDesc( SpringDescription springDesc );
				static explicit operator SpringDescription( NxSpringDesc springDesc );
				
			public:
				/// <summary>Gets or Sets the spring coefficient</summary>
				property float SpringCoefficient
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the damper coefficient</summary>
				property float DamperCoefficient 
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the target value (angle/position) of spring where the spring force is zero</summary>
				property float TargetValue
				{
					float get();
					void set( float value );
				}
		};
	};
};