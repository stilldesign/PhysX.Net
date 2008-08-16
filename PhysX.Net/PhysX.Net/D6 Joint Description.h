#pragma once

#include "Joint Description.h"
#include "Joint Limit Soft Description.h"
#include "Enums.h"
#include "Joint Limit Soft Pair Description.h"
#include "Joint Drive Description.h"

class NxD6JointDesc;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		value class JointDriveDescription;
		ref class D6Joint;
		
		public ref class D6JointDescription : JointDescription
		{
			public:
				D6JointDescription();
			internal:
				D6JointDescription( NxD6JointDesc* desc );
				
			public:
				/// <summary>Defines the linear degrees of freedom along the joint-axis</summary>
				property D6JointMotion XMotion
				{
					D6JointMotion get();
					void set( D6JointMotion value );
				}
				/// <summary>Defines the linear degrees of freedom along the joint normal axis</summary>
				property D6JointMotion YMotion
				{
					D6JointMotion get();
					void set( D6JointMotion value );
				}
				/// <summary>Defines the linear degrees of freedom along the x-axis cross y-axis axis</summary>
				property D6JointMotion ZMotion
				{
					D6JointMotion get();
					void set( D6JointMotion value );
				}
				
				property D6JointMotion Swing1Motion
				{
					D6JointMotion get();
					void set( D6JointMotion value );
				}
				property D6JointMotion Swing2Motion
				{
					D6JointMotion get();
					void set( D6JointMotion value );
				}
				property D6JointMotion TwistMotion
				{
					D6JointMotion get();
					void set( D6JointMotion value );
				}
				
				property JointLimitSoftDescription LinearLimit
				{
					JointLimitSoftDescription get();
					void set( JointLimitSoftDescription value );
				}
				/// <summary>If Swing1Motion is Limited, Swing1Limit defines the characteristics of the limit</summary>
				property JointLimitSoftDescription Swing1Limit
				{
					JointLimitSoftDescription get();
					void set( JointLimitSoftDescription value );
				}
				/// <summary>If Swing2Motion is Limited, Swing2Limit defines the characteristics of the limit</summary>
				property JointLimitSoftDescription Swing2Limit
				{
					JointLimitSoftDescription get();
					void set( JointLimitSoftDescription value );
				}
				/// <summary>If TwistMotion is Limited, TwistLimit defines the characteristics of the limit</summary>
				property JointLimitSoftPairDescription TwistLimit
				{
					JointLimitSoftPairDescription get();
					void set( JointLimitSoftPairDescription value );
				}
				
				/// <summary>Drive the x-axis linear DOF</summary>
				property JointDriveDescription XDrive
				{
					JointDriveDescription get();
					void set( JointDriveDescription value );
				}
				/// <summary>Drive the y-axis linear DOF</summary>
				property JointDriveDescription YDrive
				{
					JointDriveDescription get();
					void set( JointDriveDescription value );
				}
				/// <summary>Drive the z-axis linear DOF</summary>
				property JointDriveDescription ZDrive
				{
					JointDriveDescription get();
					void set( JointDriveDescription value );
				}
				property JointDriveDescription SwingDrive
				{
					JointDriveDescription get();
					void set( JointDriveDescription value );
				}
				property JointDriveDescription TwistDrive
				{
					JointDriveDescription get();
					void set( JointDriveDescription value );
				}
				property JointDriveDescription SLerpDrive
				{
					JointDriveDescription get();
					void set( JointDriveDescription value );
				}
				
				property Vector3 DrivePosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property Quaternion DriveOrientation
				{
					Quaternion get();
					void set( Quaternion value );
				}
				property Vector3 DriveLinearVelocity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property Vector3 DriveAngularVelocity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				property JointProjectionMode ProjectionMode
				{
					JointProjectionMode get();
					void set( JointProjectionMode value );
				}
				
				property float ProjectionDistance
				{
					float get();
					void set( float value );
				}
				
				property float ProjectionAngle
				{
					float get();
					void set( float value );
				}
				
				property float GearRatio
				{
					float get();
					void set( float value );
				}
				
				property D6JointFlag Flags
				{
					D6JointFlag get();
					void set( D6JointFlag value );
				}
			
			internal:
				property NxD6JointDesc* UnmanagedPointer
				{
					NxD6JointDesc* get();
				}
		};
	};
};