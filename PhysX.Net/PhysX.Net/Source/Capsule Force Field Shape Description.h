#pragma once

#include "Force Field Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class CapsuleForceFieldShape;
		
		public ref class CapsuleForceFieldShapeDescription : ForceFieldShapeDescription
		{
			public:
				CapsuleForceFieldShapeDescription();
			internal:
				CapsuleForceFieldShapeDescription( NxCapsuleForceFieldShapeDesc* desc );
				
			public:
				/// <summary></summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float Height
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxCapsuleForceFieldShapeDesc* UnmanagedPointer
				{
					NxCapsuleForceFieldShapeDesc* get() new;
				}
		};
	};
};