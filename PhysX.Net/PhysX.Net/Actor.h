#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "Shape.h"
#include "Element Collection.h"

using namespace System;
using namespace System::Collections::Generic;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class BodyDescription;
		ref class ShapeDescription;
		ref class Scene;
		ref class ActorDescription;
		ref class Core;
		ref class SweepQueryHit;
		ref class SweepCache;
		ref class Compartment;
		ref class UserEntitySweepQueryHitReport;
		ref class ActorFlagsWrapper;
		ref class BodyFlagsWrapper;
		
		/// <summary>Actor is the main simulation object in the physics SDK</summary>
		[System::ComponentModel::TypeConverter( System::ComponentModel::ExpandableObjectConverter::typeid )]
		public ref class Actor : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxActor* _actor;
				
				StillDesign::PhysX::Scene^ _scene;
				ElementCollection< Shape^ >^ _shapes;
				StillDesign::PhysX::Compartment^ _compartment;
				
				Object^ _userData;

				ActorFlagsWrapper^ _actorFlagsWrapper;
				BodyFlagsWrapper^ _bodyFlagsWrapper;
				
				//bool _disposing;
			
			internal:
				Actor( NxActor* actor);
			public:
				~Actor();
			protected:
				!Actor();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			//internal:
			//	property bool IsDisposing
			//	{
			//		bool get();
			//	}
				
			private:
				void CreateShapes();
			
			public:
				/// <summary>Returns this Actor's ActorDescription</summary>
				ActorDescription^ SaveToActorDescription();
				/// <summary>Returns this Actor's ActorDescription</summary>
				/// <param name="retrieveBody">Should the returned actor description contain the body description of the actor</param>
				/// <param name="retrieveShapes">Should the returned actor description contain a list of shape descriptions of the shape of the actor</param>
				ActorDescription^ SaveToActorDescription( bool retrieveBody, bool retrieveShapes );
				/// <summary>Saves the body information of a dynamic actor</summary>
				BodyDescription^ SaveBodyToDescription();
				
				/// <summary>Creates a new shape and adds it to the list of shapes of this actor</summary>
				/// <param name="shapeDescription">The descriptor for the new shape</param>
				Shape^ CreateShape( ShapeDescription^ shapeDescription );
				
				/// <summary>Wakes Up the Actor Immediately</summary>
				void WakeUp();
				/// <summary>Wakes Up the Actor Immediately</summary>
				/// <param name="sleepFrames">Determines How Long Until the Body is Put to Sleep</param>
				void WakeUp( float sleepFrames );
				/// <summary>Puts the Actor to Sleep</summary>
				void Sleep();
				
				// Forces
				/// <summary>Applies a Force (or Impulse) Defined in the Global Coordinate Frame, Acting at a Particular Point in Global Coordinates, to the Actor</summary>
				void AddForceAtPosition( Vector3 force, Vector3 position, ForceMode forceMode );
				
				/// <summary>Applies a Force (or Impulse) Defined in the Global Coordinate Frame, Acting at a Particular Point in Local Coordinates, to the Actor</summary>
				void AddForceAtLocalPosition( Vector3 force, Vector3 position );
				/// <summary>Applies a Force (or Impulse) Defined in the Global Coordinate Frame, Acting at a Particular Point in Local Coordinates, to the Actor</summary>
				void AddForceAtLocalPosition( Vector3 force, Vector3 position, ForceMode forceMode, bool wakeup );
				
				/// <summary>Applies a Force (or Impulse) Defined in the Actor Local Coordinate Frame, Acting at a Particular Point in Global Coordinates, to the Actor</summary>
				void AddLocalForceAtPosition( Vector3 force, Vector3 position, ForceMode forceMode );
				/// <summary>Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in local coordinates, to the actor</summary>
				void AddLocalForceAtLocalPosition( Vector3 force, Vector3 position, ForceMode forceMode );
				/// <summary>Applies a force (or impulse) defined in the global coordinate frame to the actor</summary>
				void AddForce( Vector3 force, ForceMode forceMode );
				/// <summary>Applies a force (or impulse) defined in the actor local coordinate frame to the actor</summary>
				void AddLocalForce( Vector3 force, ForceMode forceMode );
				/// <summary>Applies an Impulsive Torque Defined in the Global Coordinate Frame to the Actor</summary>
				void AddTorque( Vector3 torque, ForceMode forceMode );
				/// <summary>Applies an Impulsive Torque Defined in the Actor Local Coordinate Frame to the Actor</summary>
				void AddLocalTorque( Vector3 torque, ForceMode forceMode );
				
				/// <summary>Moves the Kinematic Actor to the Specified Transform</summary>
				/// <param name="globalTransform">A Rotation and/or Translation Affine Transform</param>
				void MoveGlobalPoseTo( Matrix globalTransform );
				/// <summary>Moves the Kinematic Actor to Specified Position</summary>
				/// <param name="globalPosition">A Translation Vector</param>
				void MoveGlobalPositionTo( Vector3 globalPosition );
				/// <summary>Moves the Kinematic Actor</summary>
				/// <param name="globalRotation">A Rotation Transform</param>
				void MoveGlobalOrientationTo( Matrix globalRotation );
				/// <summary>Moves the Kinematic Actor</summary>
				/// <param name="globalRotation">A Rotation Quaternion</param>
				void MoveGlobalOrientationTo( Quaternion globalRotation );
				
				/// <summary>Recomputes a Dynamic Actor's Mass Properties from its Shapes</summary>
				bool UpdateMassFromShapes( float density, float totalMass );
				
				/// <summary>Computes the total kinetic (rotational and translational) energy of the object</summary>
				float ComputeKineticEnergy();
				/// summary>Computes the velocity of a point given in world coordinates if it were attached to the actor and moving with it</summary>
				Vector3 ComputePointVelocity( Vector3 point );
				/// <summary>Computes the velocity of a point given in body local coordinates as if it were attached to the actor and moving with it</summary>
				Vector3 ComputeLocalPointVelocity( Vector3 point );
				
				/// <summary>Gets the Status of an Actor Flag</summary>
				bool ReadActorFlag( ActorFlag flag );
				/// <summary>Enables an Actor Flag</summary>
				void RaiseActorFlag( ActorFlag flag );
				/// <summary>Clears the Status of an Actor Flag</summary>
				void ClearActorFlag( ActorFlag flag );
				
				/// <summary>Gets the Status of a Flag on the Actors Body</summary>
				bool ReadBodyFlag( BodyFlag flag );
				/// <summary>Sets a Flag on the Actors Body</summary>
				void RaiseBodyFlag( BodyFlag flag );
				/// <summary>Removes Flag on the Actors Body</summary>
				void ClearBodyFlag( BodyFlag flag );
				
				/// <summary>Reset the user actor pair filtering state for this actor. This will cause filtering callbacks to be called again for any pairs involving this actor</summary>
				void ResetUserActorPairFiltering();
				
				/// <summary>The setCMassOffsetLocal*() methods set the pose of the center of mass relative to the actor</summary>
				void SetCenterOfMassOffsetLocalPose( Matrix localPose );
				/// <summary>The setCMassOffsetLocal*() methods set the pose of the center of mass relative to the actor</summary>
				void SetCenterOfMassOffsetLocalPosition( Vector3 localPosition );
				/// <summary>The setCMassOffsetLocal*() methods set the pose of the center of mass relative to the actor</summary>
				void SetCenterOfMassOffsetLocalOrientation( Matrix localOrientation );
				/// <summary>The setCMassOffsetGlobal*() methods set the pose of the center of mass relative to world space</summary>
				void SetCenterOfMassOffsetGlobalPose( Matrix globalPose );
				/// <summary>The setCMassOffsetGlobal*() methods set the pose of the center of mass relative to world space</summary>
				void SetCenterOfMassOffsetGlobalPosition( Vector3 globalPosition );
				/// <summary>The setCMassOffsetGlobal*() methods set the pose of the center of mass relative to world space</summary>
				void SetCenterOfMassOffsetGlobalOrientation( Matrix globalOrientation );
				
				/// <summary>Computes the velocity of a point given in world coordinates if it were attached to the actor and moving with it</summary>
				Vector3 GetPointVelocity( Vector3 point );
				/// <summary>Computes the velocity of a point given in body local coordinates as if it were attached to the actor and moving with it</summary>
				Vector3 GetLocalPointVelocity( Vector3 point );
				
				/// <summary>Performs a linear sweep through space with the actor</summary>
				/// <param name="motion">Length and direction of the sweep</param>
				/// <param name="flags">Flags controlling the mode of the sweep</param>
				/// <param name="userData">User data to impart to the returned data struct</param>
				/// <param name="callback">Callback function invoked on the closest hit (if any)</param>
				int LinearSweep( Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback );
				/// <summary>Performs a linear sweep through space with the actor</summary>
				/// <param name="motion">Length and direction of the sweep</param>
				/// <param name="flags">Flags controlling the mode of the sweep</param>
				/// <param name="userData">User data to impart to the returned data struct</param>
				/// <param name="callback">Callback function invoked on the closest hit (if any)</param>
				/// <param name="cache">Sweep cache to use with the query</param>
				int LinearSweep( Vector3 motion, SweepFlags flags, Object^ userData, UserEntitySweepQueryHitReport^ callback, SweepCache^ cache );
				
				/// <summary>Gets the Scene this Actor Belongs to</summary>
				property StillDesign::PhysX::Scene^ Scene
				{
					StillDesign::PhysX::Scene^ get();
				}
				
				/// <summary>Gets or Sets the Name of the Actor</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Returns True if the Actor is Dynamic, False for Static</summary>
				/// <remarks>If the Actor has a Body it is Dynamic. If it is null it is Static</remarks>
				property bool IsDynamic
				{
					bool get();
				}
				
				// Shapes
				/// <summary>Gets a Collection of Shapes Attached to this Actor</summary>
				property System::Collections::ObjectModel::ReadOnlyCollection< Shape^ >^ Shapes
				{
					System::Collections::ObjectModel::ReadOnlyCollection< Shape^ >^ get();
				}
				
				/// <summary>Gets the actor's simulation compartment, if any</summary>
				property StillDesign::PhysX::Compartment^ Compartment
				{
					StillDesign::PhysX::Compartment^ get();
				}
				
				/// <summary>Gets or Sets the Global Position</summary>
				property Vector3 GlobalPosition
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Global Pose Matrix</summary>
				property Matrix GlobalPose
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the Global Orientation/Rotation Matrix</summary>
				property Matrix GlobalOrientation
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the Global Orientation/Rotation Quaternion</summary>
				property Quaternion GlobalOrientationQuat
				{
					Quaternion get();
					void set( Quaternion value );
				}
				
				// Sleeping
				/// <summary>Gets Whether or Not the Group is Sleeping</summary>
				property bool IsGroupSleeping
				{
					bool get();
				}
				/// <summary>Is the Body Sleeping</summary>
				property bool IsSleeping
				{
					bool get();
				}
				/// <summary>Gets or Sets the Linear Velocity Below Which an Actor May Go to Sleep</summary>
				property float SleepLinearVelocity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Angular Celocity Below Which an Actor May Go to Sleep</summary>
				property float SleepAngularVelocity
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Energy Threshold Below Which an Actor May Go to Sleep</summary>
				property float SleepEnergyThreshold
				{
					float get();
					void set( float value );
				}
				
				// Velocity
				/// <summary>Gets or Sets the Linear Velocity of the Actor</summary>
				property Vector3 LinearVelocity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Angular Velocity of the Actor</summary>
				property Vector3 AngularVelocity
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the Maximum Angular Velocity Permitted for this Actor</summary>
				property float MaximumAngularVelocity
				{
					float get();
					void set( float value );
				}
				
				// Mass
				
				/// <summary>Gets or Sets the Mass of the Actor</summary>
				property float Mass
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets the Center of Mass Relative to the Actor</summary>
				property Matrix CenterOfMassLocalPose
				{
					Matrix get();
				}
				/// <summary>Gets the Center of Mass Relative to the Actor</summary>
				property Vector3 CenterOfMassLocalPosition
				{
					Vector3 get();
				}
				/// <summary>Gets the Center of Mass Relative to the Actor</summary>
				property Matrix CenterOfMassLocalOrientation
				{
					Matrix get();
				}
				
				/// <summary>Gets the center of mass pose in world space</summary>
				property Matrix CenterOfMassGlobalPose
				{
					Matrix get();
				}
				/// <summary>Gets the center of mass pose in world space</summary>
				property Vector3 CenterOfMassGlobalPosition
				{
					Vector3 get();
				}
				/// <summary>Gets the center of mass pose in world space</summary>
				property Matrix CenterOfMassGlobalOrientation
				{
					Matrix get();
				}
				
				/// <summary>Gets or Sets the inertia tensor, using a parameter specified in mass space coordinates</summary>
				property Vector3 MassSpaceInertiaTensor
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				/// <summary>Gets or Sets the inertia tensor of the actor relative to the world coordinate frame</summary>
				property Matrix GlobalInertiaTensor
				{
					Matrix get();
				}
				/// <summary>Gets or Sets the inverse of the inertia tensor of the actor relative to the world coordinate frame</summary>
				property Matrix GlobalInertiaTensorInverse
				{
					Matrix get();
				}
				
				// Damping
				/// <summary>Gets or Sets the linear damping coefficient</summary>
				property float LinearDamping
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the angular damping coefficient</summary>
				property float AngularDamping
				{
					float get();
					void set( float value );
				}
				
				// CCD
				/// <summary>Gets or Sets the CCD Motion Threshold</summary>
				property float CCDMotionThreshold
				{
					float get();
					void set( float value );
				}
				
				// Momentum
				/// <summary>Gets or Sets the linear momentum of the actor</summary>
				property Vector3 LinearMomentum
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets angular momentum of the actor</summary>
				property Vector3 AngularMomentum
				{
					Vector3 get();
					void set( Vector3 value );
				}
				
				// Group
				/// <summary>Gets or Sets the Group this Actor Belongs to</summary>
				property short Group
				{
					short get();
					void set( short value );
				}
				/// <summary>Gets or Sets dynamic actors to a dominance group</summary>
				property short DominanceGroup
				{
					short get();
					void set( short value );
				}
				
				/// <summary>Gets or Sets the solver iteration count for the body</summary>
				property int SolverIterationCount
				{
					int get();
					void set( int value );
				}
				
				/// <summary>Gets or Sets the force threshold for contact reports</summary>
				property float ContactReportThreshold
				{
					float get();
					void set( float value );
				}
				
				property ContactPairFlag ContactReportFlags
				{
					ContactPairFlag get();
					void set( ContactPairFlag value );
				}
				
				property short ForceFieldMaterial
				{
					short get();
					void set( short value );
				}
				
				/// <summary>Gets or Sets an arbitary 1:1 object</summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}

				property ActorFlagsWrapper^ ActorFlags
				{
					ActorFlagsWrapper^ get();
				}

				property BodyFlagsWrapper^ BodyFlags
				{
					BodyFlagsWrapper^ get();
				}
			
			internal:
				/// <summary>Gets a Pointer the Unmanaged Actor</summary>
				property NxActor* UnmanagedPointer
				{
					NxActor* get();
					void set( NxActor* value );
				}
		};
	};
};