#pragma once

#include "JointEnum.h"

namespace PhysX
{
	ref class Scene;
	ref class Actor;
	
	public ref class Joint abstract : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxJoint* _joint;
			PhysX::Scene^ _scene;
			JointType _type;

		internal:
			Joint(PxJoint* joint, JointType type, PhysX::Scene^ owner);
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
			/// Gets the joint type.
			/// </summary>
			property JointType Type
			{
				JointType get();
			}

			/// <summary>
			/// Gets the scene which this joint belongs to. 
			/// </summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
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