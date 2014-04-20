#pragma once

#include "Joint.h"
#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class DistanceJointDescription;
		ref class Scene;
		
		public ref class DistanceJoint : Joint
		{
			internal:
				DistanceJoint( NxDistanceJoint* distanceJoint );
			
			public:	
				void LoadFromDescription( DistanceJointDescription^ description );
				DistanceJointDescription^ SaveToDescription();
			
			internal:
				property NxDistanceJoint* UnmanagedPointer
				{
					NxDistanceJoint* get() new;
				}
		};
	};
};