#pragma once

#include "Joint Limit Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		public value class JointLimitPairDescription
		{
			public:
				JointLimitPairDescription( JointLimitDescription low, JointLimitDescription high );
			
			internal:
				static explicit operator JointLimitPairDescription( NxJointLimitPairDesc jointLimitPairDesc );
				static explicit operator NxJointLimitPairDesc( JointLimitPairDescription jointLimitPairDescription );
				
			public:
				/// <summary></summary>
				property JointLimitDescription Low;
				/// <summary></summary>
				property JointLimitDescription High;
		};
	};
};