#pragma once

#include "Joint Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PointOnLineJoint;
		
		public ref class PointOnLineJointDescription : JointDescription
		{
			public:
				PointOnLineJointDescription();
			internal:
				PointOnLineJointDescription( NxPointOnLineJointDesc* desc );
				
			internal:
				property NxPointOnLineJointDesc* UnmanagedPointer
				{
					NxPointOnLineJointDesc* get() new;
				}
		};
	};
};