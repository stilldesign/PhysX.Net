#pragma once

#include "Joint.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class FixedJointDescription;
		
		public ref class FixedJoint : Joint
		{
			internal:
				FixedJoint( NxFixedJoint* fixedJoint );
				
			public:
				void LoadFromDescription( FixedJointDescription^ description );
				FixedJointDescription^ SaveToDescription();
			
			internal:
				property NxFixedJoint* UnmanagedPointer
				{
					NxFixedJoint* get() new;
				}
		};
	};
};