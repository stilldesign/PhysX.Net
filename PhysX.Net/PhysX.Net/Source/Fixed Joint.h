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
				/// <summary>Use this for changing a significant number of joint parameters at once</summary>
				/// <param name="description">The descriptor used to set this objects state</param>
				/// <exception cref="description">Thrown when the argument is null</exception>
				void LoadFromDescription( FixedJointDescription^ description );
				/// <summary>Writes all of the object's attributes to the desc struct</summary>
				FixedJointDescription^ SaveToDescription();
			
			internal:
				property NxFixedJoint* UnmanagedPointer
				{
					NxFixedJoint* get() new;
				}
		};
	};
};