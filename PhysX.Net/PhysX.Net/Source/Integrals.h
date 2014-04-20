#pragma once 

namespace StillDesign
{
	namespace PhysX
	{
		public value class Integrals
		{
			private:
				Vector3 _centerOfMass;
				float _mass;
				Matrix inertiaTensor;
				Matrix _centerOfMassInertiaTensor;
			
			public:
				static explicit operator NxIntegrals( Integrals integral );
				static explicit operator Integrals( NxIntegrals integral );
				
				property Vector3 CenterOfMass
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property float Mass
				{
					float get();
					void set( float value );
				}
				property Matrix InertiaTensor
				{
					Matrix get();
					void set( Matrix value );
				}
				property Matrix CenterOfMassInertiaTensor
				{
					Matrix get();
					void set( Matrix value );
				}
		};
	};
};