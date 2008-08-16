#pragma once

#include "Joint Description.h"
#include "Revolute Joint.h"
#include "Motor Description.h"
#include "Spring Description.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class RevoluteJoint;
		
		public ref class RevoluteJointDescription : JointDescription
		{
			public:
				RevoluteJointDescription();
			internal:
				RevoluteJointDescription( NxRevoluteJointDesc* desc );
				
			public:
				virtual DescriptorValidity^ IsValid() override;
				
				/// <summary>Gets or Sets optional limits for the angular motion of the joint</summary>
				property JointLimitPairDescription Limit
				{
					JointLimitPairDescription get();
					void set( JointLimitPairDescription value );
				}
				/// <summary>Gets or Sets an optional motor</summary>
				property MotorDescription Motor
				{
					MotorDescription get();
					void set( MotorDescription value );
				}
				/// <summary>Gets or Sets an optional spring</summary>
				property SpringDescription Spring
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				/// <summary>Gets or Sets the distance beyond which the joint is projected</summary>
				property float ProjectionDistance
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the angle beyond which the joint is projected</summary>
				property float ProjectionAngle
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets a combination of the RevoluteJointFlag</summary>
				property RevoluteJointFlag Flags
				{
					RevoluteJointFlag get();
					void set( RevoluteJointFlag value );
				}
				/// <summary>Gets or Sets joint projection mode</summary>
				property JointProjectionMode ProjectionMode
				{
					JointProjectionMode get();
					void set( JointProjectionMode value );
				}
			
			internal:
				property NxRevoluteJointDesc* UnmanagedPointer
				{
					NxRevoluteJointDesc* get() new;
				}
		};
	};
};