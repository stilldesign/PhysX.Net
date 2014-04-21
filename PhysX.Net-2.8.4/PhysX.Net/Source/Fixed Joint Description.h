#pragma once

#include "Joint Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class FixedJoint;
		
		public ref class FixedJointDescription : JointDescription
		{
			public:
				FixedJointDescription();
			internal:
				FixedJointDescription( NxFixedJointDesc* desc );
				
			internal:
				property NxFixedJointDesc* UnmanagedPointer
				{
					NxFixedJointDesc* get() new;
				}
		};
	};
};