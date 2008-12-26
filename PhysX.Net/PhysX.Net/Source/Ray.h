#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public value class Ray
		{
			private:
				Vector3 _origin;
				Vector3 _direction;
			
			public:
				Ray( Vector3 origin, Vector3 direction );
			
			internal:
				static explicit operator NxRay( Ray ray );
				static explicit operator Ray( NxRay ray );
				
			public:
				/// <summary>Gets or Sets the origin of the ray</summary>
				property Vector3 Origin
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the direction of the ray (should be normalized)</summary>
				property Vector3 Direction
				{
					Vector3 get();
					void set( Vector3 value );
				}
		};
		
		public ref class RaycastResult abstract
		{
			private:
				bool _hit;
				Vector3 _hitPosition;
				
			protected:
				RaycastResult( bool hit, Vector3 hitPosition );
				
			public:	
				/// <summary>Did a ray hit occur?</summary>
				property bool Hit
				{
					bool get();
				}
				/// <summary>The position of the raycast hit</summary>
				property Vector3 HitPosition
				{
					Vector3 get();
				}
		};
	};
};