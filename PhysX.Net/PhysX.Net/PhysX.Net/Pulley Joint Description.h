#pragma once

#include "Joint Description.h"
#include "Enums.h"
#include "Motor Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class PulleyJoint;
		
		public ref class PulleyJointDescription : JointDescription
		{
			public:
				PulleyJointDescription();
			internal:
				PulleyJointDescription( NxPulleyJointDesc* desc );
				
			public:
				/// <summary>Gets or Sets the suspension point A in world space</summary>
				property Vector3 SuspensionPointA
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the suspension point B in world space</summary>
				property Vector3 SuspensionPointB
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the rest length of the rope connecting the two objects</summary>
				property float Distance
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets how stiff the constraint is, between 0 and 1 (stiffest)</summary>
				property float Stiffness
				{
					float get();
					void set( float value );
				}
				/// <summary>Get or Sets the transmission ratio</summary>
				property float Ratio
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the flags. A combination of the bits defined by PulleyJointFlag</summary>
				property PulleyJointFlag Flags
				{
					PulleyJointFlag get();
					void set( PulleyJointFlag value );
				}
				
				/// <summary>Gets or Sets an optional joint motor</summary>
				property MotorDescription Motor
				{
					MotorDescription get();
					void set( MotorDescription value );
				}
			
			internal:
				property NxPulleyJointDesc* UnmanagedPointer
				{
					NxPulleyJointDesc* get() new;
				}
		};
	};
};