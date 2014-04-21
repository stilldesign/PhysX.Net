#pragma once

#include "Joint.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PointInPlaneJointDescription;
		
		public ref class PointInPlaneJoint : Joint
		{
			internal:
				PointInPlaneJoint( NxPointInPlaneJoint* pointInPlaneJoint );
				
			public:
				void LoadFromDescription( PointInPlaneJointDescription^ description );
				PointInPlaneJointDescription^ SaveToDescription();
			
			internal:
				property NxPointInPlaneJoint* UnmanagedPointer
				{
					NxPointInPlaneJoint* get() new;
				}
		};
	};
};