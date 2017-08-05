#pragma once

#include "RigidActor.h"
#include "SceneEnum.h"
#include "FilterData.h"
#include "QueryFilterData.h"

namespace PhysX
{
	ref class BatchQuery;
	ref class SweepCache;
	ref class QueryFilterCallback;
	ref class LinearSweepSingleResult;
	ref class LinearSweepMultipleResult;
	ref class QueryCache;
	value class MassProperties;
	value class VelocityDeltaFromImpulseResult;
	value class LinearAngularImpulseResult;

	/// <summary>
	/// RigidBody is a base class shared between dynamic rigid body objects.
	/// </summary>
	public ref class RigidBody : RigidActor
	{
		internal:
			RigidBody(PxRigidBody* rigidBody, PhysX::IDisposable^ owner);

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
			void ClearForce(ForceMode mode);
			
			/// <summary>
			/// Applies an impulsive torque defined in the global coordinate frame to the actor. 
			/// </summary>
			void AddTorque(Vector3 force);
			/// <summary>
			/// Applies an impulsive torque defined in the global coordinate frame to the actor. 
			/// </summary>
			void AddTorque(Vector3 force, ForceMode mode, bool wake);

			/// <summary>
			/// Clears the impulsive torque defined in the global coordinate frame to the actor.
			/// </summary>
			void ClearTorque();
			/// <summary>
			/// Clears the impulsive torque defined in the global coordinate frame to the actor.
			/// </summary>
			void ClearTorque(ForceMode mode);

			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			/// <param name="density">The density of the body. Used to compute the mass of the body. The density must be greater than 0.</param>
			/// <param name="massLocalPose">The center of mass relative to the actor frame. If set to null then (0,0,0) is assumed.</param>
			/// <param name="includeNonSimShapes">True if all kind of shapes (ShapeFlag::SceneQueryShape, TriggerShape, ParticleDrain) should be taken into account.</param>
			bool UpdateMassAndInertia(float density, [Optional] Nullable<Vector3> massLocalPose, [Optional] bool includeNonSimShapes);
			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			/// <param name="shapeDensities">The per shape densities. There must be one entry for each shape which has the ShapeFlag::SimulationShape set (or for all shapes if includeNonSimShapes is set to true). Other shapes are ignored. The density values must be greater than 0.</param>
			/// <param name="massLocalPose">The center of mass relative to the actor frame. If set to null then (0,0,0) is assumed.</param>
			/// <param name="includeNonSimShapes">True if all kind of shapes (ShapeFlag::SceneQueryShape, TriggerShape, ParticleDrain) should be taken into account.</param>
			bool UpdateMassAndInertia(array<float>^ shapeDensities, Nullable<Vector3> massLocalPose, [Optional] bool includeNonSimShapes);

			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			/// <param name="body">The the rigid body for which to set the mass and centre of mass local pose properties.</param>
			/// <param name="mass">The mass of the body. Must be greater than 0.</param>
			/// <param name="massLocalPose">The center of mass relative to the actor frame. If set to null then (0,0,0) is assumed.</param>
			bool SetMassAndUpdateInertia(float mass, [Optional] Nullable<Vector3> massLocalPose);
			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			/// <param name="body">The the rigid body for which to set the mass and centre of mass local pose properties.</param>
			/// <param name="mass">The mass of the body. Must be greater than 0.</param>
			/// <param name="massLocalPose">The center of mass relative to the actor frame. If set to null then (0,0,0) is assumed.</param>
			bool SetMassAndUpdateInertia(array<float>^ shapeMasses, [Optional] Nullable<Vector3> massLocalPose);

			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddForceAtPosition(Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddForceAtPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddForceAtLocalPosition(Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the global coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the global frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddForceAtLocalPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddLocalForceAtPosition(Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in global coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddLocalForceAtPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			void AddLocalForceAtLocalPosition(Vector3 force, Vector3 position);
			/// <summary>
			/// Applies a force (or impulse) defined in the actor local coordinate frame, acting at a particular point in local coordinates, to the actor.
			/// </summary>
			/// <param name="force">Force/impulse to add, defined in the local frame. Range: force vector.</param>
			/// <param name="position">Position in the global frame to add the force at. Range: position vector.</param>
			/// <param name="forceMode">The mode to use when applying the force/impulse (see ForceMode).</param>
			/// <param name="wakeUp">Specify if the call should wake up the actor.</param>
			void AddLocalForceAtLocalPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp);

			/// <summary>
			/// Computes the velocity of a point given in world coordinates if it were attached to the specified body and moving with it.
			/// </summary>
			/// <param name="point">Point we wish to determine the velocity for, defined in the global frame. Range: position vector.</param>
			Vector3 GetVelocityAtPosition(Vector3 position);

			/// <summary>
			/// Computes the velocity of a point given in local coordinates if it were attached to the
			/// specified body and moving with it. 
			/// </summary>
			/// <param name="position">
			/// Position we wish to determine the velocity for, defined in the
			/// local frame. Range: position vector.
			/// </param>
			/// <returns>
			/// The velocity of point in the local frame.
			/// </returns>
			Vector3 GetLocalVelocityAtLocalPosition(Vector3 position);

			/// <summary>
			/// Computes the velocity of a point (offset from the origin of the body) given in world coordinates if
			/// it were attached to the specified body and moving with it.
			/// </summary>
			/// <param name="body">The rigid body the point is attached to.</param>
			/// <param name="position">Position (offset from the origin of the body) we wish to determine the velocity for, defined in the global frame. Range: position vector</param>
			/// <returns>The velocity of point (offset from the origin of the body) in the global frame.</returns>
			/// </summary>
			Vector3 GetVelocityAtOffset(Vector3 position);

			/// <summary>
			/// Performs a linear sweep through space with the body's geometry objects.
			/// Note:
			/// Supported geometries are: box, sphere, capsule, convex. Other geometry types will be ignored.
			/// The function sweeps all shapes attached to a given rigid body through space and reports the
			/// nearest object in the scene which intersects any of of the shapes swept paths. Information about
			/// the closest intersection is written to a SweepHit structure.
			/// </summary>
			/// <param name="body">The rigid body to sweep.</param>
			/// <param name="scene">The scene object to process the query.</param>
			/// <param name="unitDirection">Normalized direction of the sweep.  </param>
			/// <param name="distance">Sweep distance. Needs to be larger than 0.  </param>
			/// <param name="outputFlags">Specifies which properties should be written to the hit information.</param>
			/// <param name="filterData">If any word in filterData.data is non-zero then filterData.data will be used for filtering, otherwise shape->getSimulationFilterData() will be used instead.</param>
			/// <param name="filterCall">Custom filtering logic (optional). Only used if the corresponding PxQueryFlag flags are set. If NULL, all hits are assumed to be blocking.</param>
			/// <param name="cache">Cached hit shape (optional). Ray is tested against cached shape first then against the scene. Note: Filtering is not executed for a cached shape if supplied; instead, if a hit is found, it is assumed to be a blocking hit.</param>
			/// <param name="inflation">This parameter creates a skin around the swept geometry which increases its extents for sweeping. The sweep will register a hit as soon as the skin touches a shape, and will return the corresponding distance and normal.</param>
			LinearSweepSingleResult^ LinearSweepSingle(RigidBody^ body, PhysX::Scene^ scene, Vector3 unitDirection, float distance, HitFlag outputFlags, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCall, [Optional] QueryCache^ queryCache, [Optional] Nullable<float> inflation);

			
			LinearSweepMultipleResult^ LinearSweepMultiple(
				RigidBody^ body, 
				PhysX::Scene^ scene,
				Vector3 unitDirection, 
				float distance,
				HitFlag outputFlags,
				int hitBufferSize,
				[Optional] Nullable<QueryFilterData> filterData,
				[Optional] QueryFilterCallback^ filterCall,
				[Optional] QueryCache^ queryCache,
				[Optional] Nullable<float> inflation);

			// Extensions
			static MassProperties ComputeMassPropertiesFromShapes(array<Shape^>^ shapes);

			/// <summary>
			/// Compute the change to linear and angular velocity that would occur if an impulsive force and torque were to be applied to a specified rigid body.
			/// </summary>
			/// <param name="impulsiveForce">The impulsive force that would be applied to the specified rigid body.</param>
			/// <param name="impulsiveTorque">The impulsive torque that would be applied to the specified rigid body.</param>
			/// <returns>
			/// The change in linear velocity that would arise if impulsiveForce was to be applied to the specified rigid body.
			/// The change in angular velocity that would arise if impulsiveTorque was to be applied to the specified rigid body.
			/// </returns>
			VelocityDeltaFromImpulseResult ComputeVelocityDeltaFromImpulse(Vector3 impulsiveForce, Vector3 impulsiveTorque);
			/// <summary>
			/// Compute the change to linear and angular velocity that would occur if an impulsive force and torque were to be applied to a specified rigid body.
			/// </summary>
			/// <param name="impulsiveForce">The impulsive force that would be applied to the specified rigid body.</param>
			/// <param name="impulsiveTorque">The impulsive torque that would be applied to the specified rigid body.</param>
			/// <returns>
			/// The change in linear velocity that would arise if impulsiveForce was to be applied to the specified rigid body.
			/// The change in angular velocity that would arise if impulsiveTorque was to be applied to the specified rigid body.
			/// </returns>
			VelocityDeltaFromImpulseResult ComputeVelocityDeltaFromImpulse(Transform globalPose, Vector3 point, Vector3 impulse, float invMassScale, float invInertiaScale);

			/// <summary>
			/// Computes the linear and angular impulse vectors for a given impulse at a world space position taking a mass and inertia scale into account. 
			/// This function is useful for extracting the respective linear and angular impulses from a contact or joint when the mass / inertia ratios have been adjusted.
			/// </summary>
			/// <param name="globalPose">The body's world space transform.</param>
			/// <param name="point">The point in world space where the impulse is applied.</param>
			/// <param name="impulse">The impulse vector in world space.</param>
			/// <param name="invMassScale">The inverse mass scale.</param>
			/// <param name="invInertiaScale">The inverse inertia scale.</param>
			/// <returns>
			/// The linear impulse and the angular impulse.
			/// </returns>
			LinearAngularImpulseResult ComputeLinearAngularImpulse(Transform globalPose, Vector3 point, Vector3 impulse, float invMassScale, float invInertiaScale);

			//

			/// <summary>
			/// Returns the maximum depenetration velocity the solver is permitted to introduced.
			/// This value controls how much velocity the solver can introduce to correct
			/// for penetrations in contacts.
			/// </summary>
			property float MaxDepenetrationVelocity
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the CCD minimum advance coefficient.
			/// </summary>
			property float MinCCDAdvanceCoefficient
			{
				float get();
				void set(float value);
			}

			property RigidBodyFlag RigidBodyFlags
			{
				RigidBodyFlag get();
				void set(RigidBodyFlag value);
			}

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
			/// Gets the inverse mass of the actor.
			/// </summary>
			property float InverseMass
			{
				float get();
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
			/// Gets the diagonal inverse inertia tensor of the actor relative to the mass coordinate frame.
			/// This method retrieves a mass frame inverse inertia vector.
			/// </summary>
			property Vector3 MassSpaceInverseInertiaTensor
			{
				Vector3 get();
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