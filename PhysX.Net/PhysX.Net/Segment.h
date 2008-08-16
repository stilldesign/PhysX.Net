#pragma once

#include <NxSegment.h> 

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public value class Segment
		{
			private:
				Vector3 _p0, _p1;
			
			public:
				Segment( Vector3 point0, Vector3 point1 );
				
				float LengthSqaured();
				Vector3 ComputePoint( float t );
				
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