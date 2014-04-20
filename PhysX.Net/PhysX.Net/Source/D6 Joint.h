#pragma once

#include "Joint.h"

class NxD6Joint;

namespace StillDesign
{
	namespace PhysX
	{
		ref class D6JointDescription;
		
		public ref class D6Joint : Joint
		{
			internal:
				D6Joint( NxD6Joint* d6Joint );
				
			public:
				/// <summary>Use this for changing a significant number of joint parameters at once</summary>
				/// <param name="description">The descriptor used to set the state of the object</param>
				void LoadFromDescription( D6JointDescription^ description );
				/// <summary>Returns all of the object's attributes</summary>
				D6JointDescription^ SaveToDescription();
				
				/// <summary>Set the drive position goal position when it is being driven</summary>
				void SetDrivePosition( Vector3 value );
				/// <summary>Set the drive goal orientation when it is being driven</summary>
				void SetDriveOrientation( Quaternion value );
				/// <summary>Set the drive goal linear velocity when it is being driven</summary>
				void SetDriveLinearVelocity( Vector3 value );
				/// <summary>Set the drive angular velocity goal when it is being driven</summary>
				void SetDriveAngularVelocity( Vector3 value );
				
			internal:
				property NxD6Joint* UnmanagedPointer
				{
					NxD6Joint* get() new;
				}
		};
	};
};