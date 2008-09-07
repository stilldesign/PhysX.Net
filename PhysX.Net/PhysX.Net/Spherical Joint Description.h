#pragma once

#include "Joint Description.h"
#include "Joint Enums.h"
#include "Spring Description.h"
#include "Joint Limit Description.h"
#include "Joint Limit Pair Description.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class SphericalJoint;
		
		public ref class SphericalJointDescription : JointDescription
		{
			public:
				SphericalJointDescription();
			internal:
				SphericalJointDescription( NxSphericalJointDesc* desc );
				
			public:
				virtual bool IsValid() override;
				
				/// <summary>Gets or Sets the swing limit axis defined in the joint space of actor A</summary>
				property Vector3 SwingAxis
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the distance above which to project joint</summary>
				property float ProjectionDistance
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets rotation limits around twist axis</summary>
				property JointLimitPairDescription TwistLimit
				{
					JointLimitPairDescription get();
					void set( JointLimitPairDescription value );
				}
				/// <summary>Gets or Sets swing limits around the twist axis</summary>
				property JointLimitDescription SwingLimit
				{
					JointLimitDescription get();
					void set( JointLimitDescription value );
				}
				/// <summary>Gets or Sets a spring that works against twisting</summary>
				property SpringDescription TwistSpring
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				/// <summary>Gets or Sets a spring that works against swinging</summary>
				property SpringDescription SwingSpring
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				/// <summary>Gets or Sets a spring that lets the joint get pulled apart</summary>
				property SpringDescription JointSpring
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				/// <summary>Gets or Sets a combination of the bits defined by SphericalJointFlag</summary>
				property SphericalJointFlag Flags
				{
					SphericalJointFlag get();
					void set( SphericalJointFlag value );
				}
				/// <summary>Gets or Sets joint projection mode</summary>
				property JointProjectionMode ProjectionMode
				{
					JointProjectionMode get();
					void set( JointProjectionMode value );
				}
			
			internal:
				property NxSphericalJointDesc* UnmanagedPointer
				{
					NxSphericalJointDesc* get() new;
				}
		};
	};
};