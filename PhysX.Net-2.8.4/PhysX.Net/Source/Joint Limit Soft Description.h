#pragma once

class NxJointLimitSoftDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public value class JointLimitSoftDescription
		{
			public:
				JointLimitSoftDescription( float value, float restitution, float spring, float damping );
			
			internal:
				static JointLimitSoftDescription FromUnmanaged( NxJointLimitSoftDesc jointLimitSoftDesc );
				static NxJointLimitSoftDesc ToUnmanaged( JointLimitSoftDescription jointLimitSoftDescription );
				
			public:
				/// <summary></summary>
				property float Value;
				/// <summary></summary>
				property float Restitution;
				/// <summary></summary>
				property float Spring;
				/// <summary></summary>
				property float Damping;
		};
	};
};