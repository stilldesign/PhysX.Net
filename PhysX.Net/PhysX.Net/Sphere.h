#pragma once

#include <NxSphere.h> 

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public value class Sphere
		{
			private:
				float _radius;
				Vector3 _center;
				
			public:
				Sphere( float radius );
				Sphere( float radius, Vector3 center );
				
				static explicit operator NxSphere( Sphere sphere );
				static explicit operator Sphere( NxSphere sphere );
				
				bool IsValid();
				bool Contains( Vector3 point );
				bool Contains( Sphere sphere );
				bool Intersects( Sphere sphere );
				
				property float Radius
				{
					float get();
					void set( float value );
				}
				property Vector3 Center
				{
					Vector3 get();
					void set( Vector3 value );
				}
		};
	};
};