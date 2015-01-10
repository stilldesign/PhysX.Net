#pragma once

#include "JointEnum.h"
#include "ConstraintEnum.h"

namespace PhysX
{
	ref class Physics;
	ref class Actor;
	ref class Constraint;
	ref class Serializable;
	
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

			/// <summary>
			/// Gets an object which is responsible for serialization of this type.
			/// </summary>
			Serializable^ AsSerializable();

			//

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
			property PhysX::Actor^ Actor0
			{
				PhysX::Actor^ get();
			}
			/// <summary>
			/// Gets the second actor for this joint.
			/// </summary>
			property PhysX::Actor^ Actor1
			{
				PhysX::Actor^ get();
			}

			/// <summary>
			/// Gets or sets the joint local pose for an actor 0.
			/// </summary>
			property Matrix LocalPose0
			{
				Matrix get();
				void set(Matrix value);
			}
			/// <summary>
			/// Gets or sets the joint local pose for an actor 1.
			/// </summary>
			property Matrix LocalPose1
			{
				Matrix get();
				void set(Matrix value);
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
			property PhysX::ConstraintFlag ConstraintFlag
			{
				PhysX::ConstraintFlag get();
				void set(PhysX::ConstraintFlag value);
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