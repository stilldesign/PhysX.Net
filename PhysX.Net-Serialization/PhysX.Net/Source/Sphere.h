#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public value class Sphere
		{
			public:
				Sphere( float radius );
				Sphere( float radius, Vector3 center );
				
				static explicit operator NxSphere( Sphere sphere );
				static explicit operator Sphere( NxSphere sphere );
				
				bool IsValid();
				bool Contains( Vector3 point );
				bool Contains( Sphere sphere );
				bool Intersects( Sphere sphere );
				
				property float Radius;
				property Vector3 Center;
		};
	};
};