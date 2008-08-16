#pragma once

#include "Joint Enums.h"
#include "IDisposable.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class Actor;
		ref class JointDescription;
		ref class Joint;
		ref class Actor;
		value class LimitPlane;
		
		public ref class Joint abstract : StillDesign::PhysX::IDisposable
		{
			public:
				ref class LimitPlaneCollection : ReadOnlyListNotifiable<LimitPlane>
				{
					
				};
			
			//
			
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			protected:
				NxJoint* _joint;
				
				StillDesign::PhysX::Scene^ _scene;
				
				Actor^ _actor1;
				Actor^ _actor2;
				
				ListNotifiable<LimitPlane, LimitPlaneCollection^>^ _limitPlanes;
				
				Object^ _userData;
				
			internal:
				Joint( NxJoint* joint );
			public:
				~Joint();
			protected:
				!Joint();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			protected:
				void SaveToDescription( JointDescription^ jointDescription );
				void LoadFromDescription( JointDescription^ jointDescription );
				
			public:
				void AddLimitPlane( LimitPlane limitPlane );
				bool RemoveLimitPlane( LimitPlane limitPlane );
				void RemoveLimitPlane( int index );
				
				/// <summary>Sets the limit point</summary>
				void SetLimitPoint( Vector3 point );
				/// <summary>Sets the limit point</summary>
				void SetLimitPoint( Vector3 point, bool isPointOnActor2 );
				/// <summary>Retrieves the global space limit point</summary>
				Nullable<Vector3> GetLimitPoint();
				
				/// <summary>Gets or Sets the Name of the Joint</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets or Sets the Scene this Joint Belongs to</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				/// <summary>Gets the First Actor of the Joint</summary>
				property Actor^ Actor1
				{
					Actor^ get();
				}
				/// <summary>Gets the Second Actor of the Joint</summary>
				property Actor^ Actor2
				{
					Actor^ get();
				}
				
				/// <summary>Gets or Sets the Anchor Position in World Space</summary>
				property Vector3 GlobalAnchor
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Axis in World Space</summary>
				property Vector3 GlobalAxis
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets the Current State of the Joint</summary>
				property JointState State
				{
					JointState get();
				}
				
				/// <summary>Gets or Sets the Amount of Force that can be Applied Before the Joint Breaks Apart</summary>
				property float BreakableMaxForce
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Amount of Torque that can be Applied Before the Joint Breaks Apart</summary>
				property float BreakableMaxTorque
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
				
				/// <summary>Gets the Joint Type</summary>
				property JointType Type
				{
					JointType get();
				}
				
				/// <summary></summary>
				property LimitPlaneCollection^ LimitPlanes
				{
					LimitPlaneCollection^ get();
				}
				
				/// <summary>Gets or Sets an arbitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxJoint* UnmanagedPointer
				{
					NxJoint* get();
				}
		};
	};
};