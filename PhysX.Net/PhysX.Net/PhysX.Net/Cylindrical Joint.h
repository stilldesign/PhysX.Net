#pragma once

#include "Joint.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class CylindricalJointDescription;
		ref class Scene;
		
		public ref class CylindricalJoint : Joint
		{
			internal:
				CylindricalJoint( NxCylindricalJoint* cylindricalJoint );
			
			public:
				void LoadFromDescription( CylindricalJointDescription^ description );
				CylindricalJointDescription^ SaveToDescription();
			
			internal:
				property NxCylindricalJoint* UnmanagedPointer
				{
					NxCylindricalJoint* get() new;
				}
		};
	};
};