#pragma once

class NxJointLimitSoftDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public value class JointLimitSoftDescription
		{
			private:
				float _value, _restitution, _spring, _damping;
			
			public:
				JointLimitSoftDescription( float value, float restitution, float spring, float damping );
			
			internal:
				static JointLimitSoftDescription FromUnmanaged( NxJointLimitSoftDesc jointLimitSoftDesc );
				static NxJointLimitSoftDesc ToUnmanaged( JointLimitSoftDescription jointLimitSoftDescription );
				
			public:
				/// <summary></summary>
				property float Value
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float Restitution
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float Spring
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float Damping
				{
					float get();
					void set( float value );
				}
		};
	};
};