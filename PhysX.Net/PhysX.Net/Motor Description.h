#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class MotorDescription
		{
			private:
				float _velocityTarget;
				float _maximumForce;
				bool _freeSpin;
				
			public:
				MotorDescription( float velocityTarget, float maxForce, bool freeSpinEnabled );
				
			internal:
				static explicit operator MotorDescription( NxMotorDesc motorDescription );
				static explicit operator NxMotorDesc( MotorDescription motorDescription );
				
			public:
				DescriptorValidity^ IsValid();
				
				/// <summary></summary>
				property float VelocityTarget
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float MaximumForce
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property bool FreeSpinEnabled
				{
					bool get();
					void set( bool value );
				}
		};
	};
};