#pragma once

#include "Joint Enums.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		ref class Actor;
		
		public ref class JointDescription abstract
		{
			protected:
				NxJointDesc* _desc;
			
			private:
				Actor^ _actor1;
				Actor^ _actor2;
				
				String^ _name;
				
				Object^ _userData;
				
			protected:
				JointDescription( NxJointDesc* jointDesc );
			public:
				~JointDescription();
			protected:
				!JointDescription();
			
			public:
				virtual bool IsValid();
				/// <summary>(Re)sets the structure to the default</summary>
				virtual void SetToDefault();
				
				/// <summary>Set the localAnchor[] members using a world space point</summary>
				/// <param name="anchor">Global frame anchor point</param>
				void SetGlobalAnchor( Vector3 anchor );
				/// <summary>Set the local axis/normal using a world space axis</summary>
				/// <param name="axis">Global frame axis</param>
				void SetGlobalAxis( Vector3 axis );
				
			private:
				void _actor1_OnDisposed( System::Object^ sender, EventArgs^ e );
				void _actor2_OnDisposed( System::Object^ sender, EventArgs^ e );
				
			internal:
				static NxJointDesc* CopyToUnmanagedPointer( NxJointDesc* desc );
				static JointDescription^ CopyToManagedReference( NxJointDesc* desc );
				
			public:
				/// <summary>Gets the Type of Joint</summary>
				property JointType Type
				{
					JointType get();
				}
				/// <summary>Gets or Sets actor 1</summary>
				property Actor^ Actor1
				{
					Actor^ get();
					void set( Actor^ value );
				}
				/// <summary>Gets or Sets actor 2</summary>
				property Actor^ Actor2
				{
					Actor^ get();
					void set( Actor^ value );
				}
				
				/// <summary>Gets or Sets the name of the joint</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the X axis of joint space, in Actor1's space, orthogonal to LocalAxis1</summary>
				property Vector3 LocalNormal1
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the X axis of joint space, in Actor2's space, orthogonal to LocalAxis2</summary>
				property Vector3 LocalNormal2
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets the Z axis of joint space, in Actor1's space. This is the primary axis of the joint</summary>
				property Vector3 LocalAxis1
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Z axis of joint space, in Actor2's space. This is the primary axis of the joint</summary>
				property Vector3 LocalAxis2
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets the attachment point of joint in Actor1's space</summary>
				property Vector3 LocalAnchor1
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the attachment point of joint in Actor2's space</summary>
				property Vector3 LocalAnchor2
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets the maximum linear force that the joint can withstand before breaking, must be positive</summary>
				property float MaxForce
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the maximum angular force (torque) that the joint can withstand before breaking, must be positive</summary>
				property float MaxTorque
				{
					float get();
					void set( float value );
				}
				/// <summary>Extrapolation factor for solving joint constraints</summary>
				property float SolverExtrapolationFactor
				{
					float get();
					void set( float value );
				}
				/// <summary>Switch to acceleration based spring</summary>
				property JointAccelerationSpringType AccelerationSpring
				{
					JointAccelerationSpringType get();
					void set( JointAccelerationSpringType value );
				}
				
				/// <summary>Gets or Sets the a combination of the bits defined by JointFlag</summary>
				property JointFlag JointFlags
				{
					JointFlag get();
					void set( JointFlag value );
				}
				
				/// <summary>Gets or Sets an arbitary 1:1 object</summary>
				property Object^ UserData
				{
					virtual Object^ get();
					virtual void set( Object^ value );
				}
			
			internal:
				property NxJointDesc* UnmanagedPointer
				{
					NxJointDesc* get();
				}
		};
	};
};