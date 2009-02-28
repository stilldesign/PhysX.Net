#pragma once

#include "Joint Description.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class CylindricalJoint;
		
		public ref class CylindricalJointDescription : JointDescription
		{
			public:
				CylindricalJointDescription();
			internal:
				CylindricalJointDescription( NxCylindricalJointDesc* desc );
				
			internal:
				property NxCylindricalJointDesc* UnmanagedPointer
				{
					NxCylindricalJointDesc* get() new;
				}
		};
	};
};