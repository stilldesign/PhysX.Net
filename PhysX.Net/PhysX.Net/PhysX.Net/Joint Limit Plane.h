#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public value class LimitPlane
		{
			private:
				Vector3 _normal;
				float _d;
				
				float _restitution;
			
			public:
				LimitPlane( Vector3 normal, Vector3 pointInPlane, float restitution );
				LimitPlane( Plane plane, float restitution );
				
				static explicit operator Plane( LimitPlane limitPlane );
				
				/// <summary></summary>
				Vector3 PointInPlane();
				
				/// <summary></summary>
				property Vector3 Normal
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary></summary>
				property float Distance
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float Resitution
				{
					float get();
					void set( float value );
				}
		};
	};
};