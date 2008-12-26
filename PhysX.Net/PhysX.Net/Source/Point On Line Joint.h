#pragma once

#include "Joint.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PointOnLineJointDescription;
		
		public ref class PointOnLineJoint : Joint
		{
			internal:
				PointOnLineJoint( NxPointOnLineJoint* pointOnLineJoint );
				
			public:
				void LoadFromDescription( PointOnLineJointDescription^ description );
				PointOnLineJointDescription^ SaveToDescription();
			
			internal:
				property NxPointOnLineJoint* UnmanagedPointer
				{
					NxPointOnLineJoint* get() new;
				}
		};
	};
};