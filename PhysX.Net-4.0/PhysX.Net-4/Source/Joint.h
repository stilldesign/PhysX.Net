#pragma once

#include "JointEnum.h"
#include "ConstraintEnum.h"

namespace PhysX
{
	ref class Physics;
	ref class RigidActor;
	ref class Constraint;
	ref class Serializable;
	ref class Scene;
	
	public ref class Joint abstract : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxJoint* _joint;
			PhysX::Physics^ _owner;
			PhysX::Constraint^ _constraint;

		internal:
			Joint(PxJoint* joint, PhysX::Physics^ owner);
		public:
			~Joint();
		protected:
			!Joint();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			//

			/// <summary>
			/// Set the actors for this joint.
			/// An actor may be NULL to indicate the world frame. At most one of the actors may be NULL.
			/// </summary>
			/// <param name="actor0">The first actor.</param>
			/// <param name="actor1">The second actor</param>
			void SetActors(RigidActor^ actor0, RigidActor^ actor1);

			/// <summary>
			/// Get the relative angular velocity of the joint.
			/// This function returns the angular velocity of actor1 relative to actor0. The value is returned
			/// in the constraint frame of actor0.
			/// </summary>
			Vector3 GetRelativeAngularVelocity();

			/// <summary>
			/// Get the relative linear velocity of the joint.
			/// This function returns the linear velocity of the origin of the constraint frame of actor1, relative
			/// to the origin of the constraint frame of actor0.The value is returned in the constraint frame of actor0.
			/// </summary>
			Vector3 GetRelativeLinearVelocity();

			/// <summary>
			/// Get the relative pose for this joint.
			/// This function returns the pose of the joint frame of actor1 relative to actor0.
			/// </summary>
			Matrix GetRelativeTransform();

			//

			/// <summary>
			/// Gets an object which is responsible for serialization of this type.
			/// </summary>
			Serializable^ AsSerializable();

			//

			/// <summary>
			/// Helper function to setup a joint's global frame.
			/// This replaces the following functions from previous SDK versions
			/// The function sets the joint's localPose using world-space input parameters.
			/// </summary>
			void SetGlobalFrame(Vector3 anchor, Vector3 axis);

			//

			/// <summary>
			/// Retrieves the scene which this joint belongs to.
			/// Returns: Owner Scene. NULL if not part of a scene.
			/// </summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Retrieves the PxConstraint corresponding to this joint.
			/// This can be used to determine, among other things, the force applied at the joint.
			/// </summary>
			property PhysX::Constraint^ Constraint
			{
				PhysX::Constraint^ get();
			}

			/// <summary>
			/// Gets the joint type.
			/// </summary>
			property JointType Type
			{
				JointType get();
			}

			/// <summary>
			/// Gets the first actor for this joint.
			/// </summary>
			property PhysX::RigidActor^ Actor0
			{
				PhysX::RigidActor^ get();
			}
			/// <summary>
			/// Gets the second actor for this joint.
			/// </summary>
			property PhysX::RigidActor^ Actor1
			{
				PhysX::RigidActor^ get();
			}

			/// <summary>
			/// Gets or sets the joint local pose for an actor 0.
			/// </summary>
			property Transform LocalPose0
			{
				Transform get();
				void set(Transform value);
			}
			/// <summary>
			/// Gets or sets the joint local pose for an actor 1.
			/// </summary>
			property Transform LocalPose1
			{
				Transform get();
				void set(Transform value);
			}

			/// <summary>
			/// Gets or sets the break force.
			/// </summary>
			property float BreakForce
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the break force torque.
			/// </summary>
			property float BreakForceTorque
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets constraint flags for this joint to a specified value.
			/// </summary>
			property PhysX::ConstraintFlag ConstraintFlags
			{
				PhysX::ConstraintFlag get();
				void set(PhysX::ConstraintFlag value);
			}

			/// <summary>
			/// Gets or sets the inverse mass scale for actor0.
			/// </summary>
			property float InverseMassScale0
			{
				float get();
				void set(float value);
			}
			/// <summary>
			/// Gets or sets the inverse mass scale for actor1.
			/// </summary>
			property float InverseMassScale1
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the inverse inertia scale for actor0.
			/// </summary>
			property float InverseInertiaScale0
			{
				float get();
				void set(float value);
			}
			/// <summary>
			/// Gets or sets the inverse inertia scale for actor1.
			/// </summary>
			property float InverseInertiaScale1
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the name of the joint.
			/// </summary>
			property String^ Name
			{
				String^ get();
				void set(String^ value);
			}

			/// <summary>
			/// Gets or sets an object, usually to create a 1:1 relationship with a user object.
			/// </summary>
			property Object^ UserData;

		internal:
			property PxJoint* UnmanagedPointer
			{
				PxJoint* get();
			}
	};
};