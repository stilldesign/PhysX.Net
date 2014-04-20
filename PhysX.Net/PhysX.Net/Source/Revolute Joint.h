#pragma once

#include "Joint.h"
#include "Motor Description.h"
#include "Spring Description.h"
#include "Joint Limit Pair Description.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class RevoluteJointDescription;
		
		public ref class RevoluteJoint : Joint
		{
			internal:
				RevoluteJoint( NxRevoluteJoint* revoluteJoint );
				
			public:
				void LoadFromDescription( RevoluteJointDescription^ description );
				RevoluteJointDescription^ SaveToDescription();
				
				/// <summary>Gets or Sets the joint limits</summary>
				property JointLimitPairDescription Limits
				{
					JointLimitPairDescription get();
					void set( JointLimitPairDescription value );
				}
				/// <summary>Gets or Sets motor parameters</summary>
				property MotorDescription Motor
				{
					MotorDescription get();
					void set( MotorDescription value );
				}
				/// <summary>Gets or Sets spring settings</summary>
				property SpringDescription Spring
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				/// <summary>Gets the current revolute joint angle</summary>
				property float Angle
				{
					float get();
				}
				/// <summary>Gets the revolute joint angle's rate of change (angular velocity)</summary>
				property float Velocity
				{
					float get();
				}
				/// <summary>Gets or Sets the revolute joints flags</summary>
				property RevoluteJointFlag Flags
				{
					RevoluteJointFlag get();
					void set( RevoluteJointFlag value );
				}
				/// <summary>Gets or Sets the joints projection mode</summary>
				property JointProjectionMode ProjectionMode
				{
					JointProjectionMode get();
					void set( JointProjectionMode value );
				}
			
			internal:
				property NxRevoluteJoint* UnmanagedPointer
				{
					NxRevoluteJoint* get() new;
				}
		};
	};
};