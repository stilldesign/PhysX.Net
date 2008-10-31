#pragma once

using namespace System;

class NxJointLimitDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public value class JointLimitDescription
		{
			private:
				float _value, _restitution, _hardness;
			
			public:
				JointLimitDescription( float value, float restitution, float hardness );
				
			internal:
				static explicit operator JointLimitDescription( NxJointLimitDesc jointLimitDescription );
				static explicit operator NxJointLimitDesc( JointLimitDescription jointLimitDescription );
				
			public:
				property float Value
				{
					float get();
					void set( float value );
				}
				property float Restitution
				{
					float get();
					void set( float value );
				}
				property float Hardness
				{
					float get();
					void set( float value );
				}
		};
	};
};