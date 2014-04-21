#pragma once

#include "Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class CapsuleShape;
		
		public ref class CapsuleShapeDescription : ShapeDescription
		{
			public:
				CapsuleShapeDescription();
				CapsuleShapeDescription( float radius, float height );
				
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
				property CapsuleShapeFlag Flags
				{
					CapsuleShapeFlag get();
					void set( CapsuleShapeFlag value );
				}
			
			internal:
				property NxCapsuleShapeDesc* UnmanagedPointer
				{
					NxCapsuleShapeDesc* get() new;
				}
		};
	};
};