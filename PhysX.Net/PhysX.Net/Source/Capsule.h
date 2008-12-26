#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		value class Segment;
		
		public value class Capsule
		{
			private:
				Vector3 _p0, _p1;
				
				float _radius;
			
			public:
				Capsule( Segment segment, float radius );
				Capsule( Vector3 p0, Vector3 p1, float radius );
			
			internal:
				static explicit operator Capsule( NxCapsule capsule );
				static explicit operator NxCapsule( Capsule capsule );
			public:
				static operator Segment( Capsule capsule );
				
				property Vector3 Point0
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property Vector3 Point1
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				property float Radius
				{
					float get();
					void set( float value );
				}
		};
	};
};