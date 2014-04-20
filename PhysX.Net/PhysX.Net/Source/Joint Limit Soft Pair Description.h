#pragma once

#include "Joint Limit Soft Description.h"

class NxJointLimitSoftPairDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public value class JointLimitSoftPairDescription
		{
			private:
				JointLimitSoftDescription _low;
				JointLimitSoftDescription _high;
				
			internal:
				static JointLimitSoftPairDescription FromUnmanaged( NxJointLimitSoftPairDesc jointLimitSoftPairDescription );
				static NxJointLimitSoftPairDesc ToUnmanaged( JointLimitSoftPairDescription jointLimitSoftPairDescription );
				
			public:
				/// <summary></summary>
				property JointLimitSoftDescription Low
				{
					JointLimitSoftDescription get();
					void set( JointLimitSoftDescription value );
				}
				/// <summary></summary>
				property JointLimitSoftDescription High
				{
					JointLimitSoftDescription get();
					void set( JointLimitSoftDescription value );
				}
		};
	};
};