#pragma once

#include "Joint Description.h"
#include "Enums.h"
#include "Spring Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PrismaticJoint;
		
		public ref class PrismaticJointDescription : JointDescription
		{
			public:
				PrismaticJointDescription();
			internal:
				PrismaticJointDescription( NxPrismaticJointDesc* desc );
				
			internal:
				property NxPrismaticJointDesc* UnmanagedPointer
				{
					NxPrismaticJointDesc* get() new;
				}
		};
	};
};