#pragma once

#include "Joint.h"
#include "Joint Enums.h"
#include "Motor Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PulleyJointDescription;
		
		public ref class PulleyJoint : Joint
		{
			internal:
				PulleyJoint( NxPulleyJoint* pulleyJoint );
			
			public:
				void LoadFromDescription( PulleyJointDescription^ description );
				PulleyJointDescription^ SaveToDescription();
				
				/// <summary>Gets or Sets the flags. This is a combination of the PulleyJointFlag</summary>
				property PulleyJointFlag Flags
				{
					PulleyJointFlag get();
					void set( PulleyJointFlag value );
				}
				
				/// <summary>Gets back the motor parameters</summary>
				property MotorDescription Motor
				{
					MotorDescription get();
					void set( MotorDescription value );
				}
				/// <summary>Gets if the motor is enabled or not</summary>
				property bool IsMotorEnabled
				{
					bool get();
				}
			
			internal:
				property NxPulleyJoint* UnmanagedPointer
				{
					NxPulleyJoint* get() new;
				}
		};
	};
};