#pragma once

#include "Base Shape.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		value class Capsule;
		ref class CapsuleShape;
		ref class Scene;
		ref class CapsuleShapeDescription;
		
		public ref class CapsuleShape : Shape
		{
			internal:
				CapsuleShape( NxCapsuleShape* capsuleShape );
				
			public:
				CapsuleShapeDescription^ SaveToDescription();
				
				void SetDimensions( float radius, float height );
				
				Capsule GetWorldSpaceCapsule();
				
				property float Radius
				{
					float get();
					void set( float value );
				}
				property float Height
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxCapsuleShape* UnmanagedPointer
				{
					NxCapsuleShape* get() new;
				}
		};
	};
};