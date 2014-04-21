#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		value class Segment;
		
		public value class Capsule
		{
			public:
				Capsule( Segment segment, float radius );
				Capsule( Vector3 p0, Vector3 p1, float radius );
			
			internal:
				static explicit operator Capsule( NxCapsule capsule );
				static explicit operator NxCapsule( Capsule capsule );
			public:
				static operator Segment( Capsule capsule );
				
				property Vector3 Point0;
				property Vector3 Point1;
				
				property float Radius;
		};
	};
};