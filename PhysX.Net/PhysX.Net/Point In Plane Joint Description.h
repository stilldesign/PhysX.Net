#pragma once

#include "Joint Description.h"
#include "Enums.h"
#include "Spring Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PointInPlaneJoint;
		
		public ref class PointInPlaneJointDescription : JointDescription
		{
			public:
				PointInPlaneJointDescription();
			internal:
				PointInPlaneJointDescription( NxPointInPlaneJointDesc* desc );
				
			internal:
				property NxPointInPlaneJointDesc* UnmanagedPointer
				{
					NxPointInPlaneJointDesc* get() new;
				}
		};
	};
};