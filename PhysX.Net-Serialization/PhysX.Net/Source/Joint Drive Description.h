#pragma once

#include "Enums.h"

class NxJointDriveDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public value class JointDriveDescription
		{
			float _damping;
			D6JointDriveType _type;
			float _forceLimit;
			float _spring;
			
			public:
				JointDriveDescription( float damping, D6JointDriveType driveType, float forceLimit, float spring );
			
			internal:
				static JointDriveDescription FromUnmanaged( NxJointDriveDesc jointDriveDescription );
				static NxJointDriveDesc ToUnmanaged( JointDriveDescription jointDriveDescription );
				
			public:	
				/// <summary></summary>
				property float Spring
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float Damping
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property D6JointDriveType DriveType
				{
					D6JointDriveType get();
					void set( D6JointDriveType value );
				}
				/// <summary></summary>
				property float ForceLimit
				{
					float get();
					void set( float value );
				}
		};
	};
};