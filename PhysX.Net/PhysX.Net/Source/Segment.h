#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class Segment
		{
			public:
				Segment( Vector3 point0, Vector3 point1 );
				
				float LengthSqaured();
				Vector3 ComputePoint( float t );
				
				property Vector3 Point0;
				property Vector3 Point1;
				
				property Vector3 Origin
				{
					Vector3 get();
				}
				property Vector3 Direction
				{
					Vector3 get();
				}
				property float Length
				{
					float get();
				}
		};
	};
};