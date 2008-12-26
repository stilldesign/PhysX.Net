#pragma once

#include "Joint Limit Description.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		public value class JointLimitPairDescription
		{
			private:
				JointLimitDescription _low;
				JointLimitDescription _high;
			
			public:
				JointLimitPairDescription( JointLimitDescription low, JointLimitDescription high );
			
			internal:
				static explicit operator JointLimitPairDescription( NxJointLimitPairDesc jointLimitPairDesc );
				static explicit operator NxJointLimitPairDesc( JointLimitPairDescription jointLimitPairDescription );
				
			public:
				/// <summary></summary>
				property JointLimitDescription Low
				{
					JointLimitDescription get();
					void set( JointLimitDescription value );
				}
				/// <summary></summary>
				property JointLimitDescription High
				{
					JointLimitDescription get();
					void set( JointLimitDescription value );
				}
		};
	};
};