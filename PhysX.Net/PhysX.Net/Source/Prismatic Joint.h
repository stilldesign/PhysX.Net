#pragma once

#include "Joint.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PrismaticJointDescription;
		ref class Scene;
		
		public ref class PrismaticJoint : Joint
		{
			internal:
				PrismaticJoint( NxPrismaticJoint* prismaticJoint );
				
			public:
				void LoadFromDescription( PrismaticJointDescription^ description );
				PrismaticJointDescription^ SaveToDescription();
			
			internal:
				property NxPrismaticJoint* UnmanagedPointer
				{
					NxPrismaticJoint* get() new;
				}
		};
	};
};