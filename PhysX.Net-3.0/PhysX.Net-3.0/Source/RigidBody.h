#pragma once

#include "RigidActor.h"
#include <PxActor.h>
#include <PxRigidBody.h> 

namespace PhysX
{
	/// <summary>
	/// RigidBody is a base class shared between dynamic rigid body objects.
	/// </summary>
	public ref class RigidBody : RigidActor
	{
		internal:
			RigidBody(PxRigidBody* rigidBody, PhysX::Physics^ owner);

		public:
			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame to the actor.
			/// </summary>
			void AddForce(Vector3 force);
			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame to the actor.
			/// </summary>
			void AddForce(Vector3 force, ForceMode mode, bool wake);

			/// <summary>
			/// Clears the accumulated forces (sets the accumulated force back to zero).
			/// </summary>
			void ClearForce();
			/// <summary>
			/// Clears the accumulated forces (sets the accumulated force back to zero).
			/// </summary>
			void ClearForce(ForceMode mode, bool wake);
			
			/// <summary>
			/// Clears the impulsive torque defined in the global coordinate frame to the actor.
			/// </summary>
			void ClearTorque();
			/// <summary>
			/// Clears the impulsive torque defined in the global coordinate frame to the actor.
			/// </summary>
			void ClearTorque(ForceMode mode, bool wake);

			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			/// <param name="body">The the rigid body for which to set the mass and centre of mass local pose properties.</param>
			/// <param name="density">The density of the body. Used to compute the mass of the body. The density must be greater than 0.</param>
			/// <param name="massLocalPose">The center of mass relative to the actor frame. If set to null then (0,0,0) is assumed.</param>
			bool UpdateMassAndInertia(RigidBody^ body, float density, [Optional] Nullable<Vector3> massLocalPose);

			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			/// <param name="body">The the rigid body for which to set the mass and centre of mass local pose properties.</param>
			/// <param name="mass">The mass of the body. Must be greater than 0.</param>
			/// <param name="massLocalPose">The center of mass relative to the actor frame. If set to null then (0,0,0) is assumed.</param>
			bool SetMassAndUpdateInertia(RigidBody^ body, float mass, [Optional] Nullable<Vector3> massLocalPose);

			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddForceAtPosition(RigidBody^ body, Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddForceAtPosition(RigidBody^ body, Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddForceAtLocalPosition(RigidBody^ body, Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddForceAtLocalPosition(RigidBody^ body, Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddLocalForceAtPosition(RigidBody^ body, Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddLocalForceAtPosition(RigidBody^ body, Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddLocalForceAtLocalPosition(RigidBody^ body, Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="body">The rigid body to apply the force to.</param>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddLocalForceAtLocalPosition(RigidBody^ body, Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Computes the velocity of a point given in world coordinates if it were attached to the specified body and moving with it.
			/// </summary>
			/// <param name="body">The rigid body the point is attached to.</param>
			/// <param name="point">Point we wish to determine the velocity for, defined in the global frame. Range: position vector.</param>
			Vector3 GetPointVelocity(RigidBody^ body, Vector3 point);

			//

			/// <summary>
			/// Gets or sets the center of mass pose relative to the actor frame.
			/// </summary>
			property Matrix CenterOfMassLocalPose
			{
				Matrix get();
				void set(Matrix value);
			}

			/// <summary>
			/// Gets or sets the mass of the actor.
			/// </summary>
			property float Mass
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the inertia tensor, using a parameter specified in mass space coordinates.
			/// </summary>
			property Vector3 MassSpaceInertiaTensor
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the linear velocity of an actor.
			/// </summary>
			property Vector3 LinearVelocity
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the angular velocity of the actor.
			/// </summary>
			property Vector3 AngularVelocity
			{
				Vector3 get();
				void set(Vector3 value);
			}

		internal:
			property PxRigidBody* UnmanagedPointer
			{
				PxRigidBody* get();
			}
	};
};