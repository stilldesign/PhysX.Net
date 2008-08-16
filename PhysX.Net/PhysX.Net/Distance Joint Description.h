#pragma once

#include "Joint Description.h"
#include "Enums.h"
#include "Spring Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class DistanceJoint;
		
		public ref class DistanceJointDescription : JointDescription
		{
			public:
				DistanceJointDescription();
			internal:
				DistanceJointDescription( NxDistanceJointDesc* desc );
				
			public:
				property float MinimumDistance
				{
					float get();
					void set( float value );
				}
				property float MaximumDistance
				{
					float get();
					void set( float value );
				}
				
				property SpringDescription Spring
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				
				property DistanceJointFlag Flags
				{
					DistanceJointFlag get();
					void set( DistanceJointFlag value );
				}
			
			internal:
				property NxDistanceJointDesc* UnmanagedPointer
				{
					NxDistanceJointDesc* get() new;
				}
		};
	};
};