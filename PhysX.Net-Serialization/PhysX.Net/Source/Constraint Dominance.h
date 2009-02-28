#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class ConstraintDominance
		{
			private:
				float _a;
				float _b;
			
			public:
				ConstraintDominance( float a, float b );
				
			internal:
				static explicit operator NxConstraintDominance( ConstraintDominance dominance );
				static explicit operator ConstraintDominance( NxConstraintDominance dominance );
				
			public:
				property float Dominance0
				{
					float get();
					void set( float value );
				}
				property float Dominance1
				{
					float get();
					void set( float value );
				}
		};
	};
};