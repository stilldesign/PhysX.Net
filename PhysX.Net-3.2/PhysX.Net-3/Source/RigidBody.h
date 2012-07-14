#pragma once

#include "RigidActor.h"
#include "SceneEnum.h"
#include "FilterData.h"
#include <PxActor.h>
#include <PxRigidBody.h> 

namespace PhysX
{
	ref class BatchQuery;
	value class SceneQueryFilterData;
	ref class SweepCache;

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
			void ClearTorque(ForceMode mode, bool wake);

			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			/// <param name="density">The density of the body. Used to compute the mass of the body. The density must be greater than 0.</param>
			/// <param name="massLocalPose">The center of mass relative to the actor frame. If set to null then (0,0,0) is assumed.</param>
			bool UpdateMassAndInertia(float density, [Optional] Nullable<Vector3> massLocalPose);
			/// <summary>
			/// Computation of mass properties for a rigid body actor.
			/// </summary>
			bool UpdateMassAndInertia(array<float>^ shapeDensities, Nullable<Vector3> massLocalPose);

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
			/// Supported geometries are: PxBoxGeometry, PxSphereGeometry, PxCapsuleGeometry. Other geometry types
			/// will be ignored.
			/// Internally this call is mapped to PxBatchQuery::linearCompoundGeometrySweepSingle().
			/// The function sweeps all specified geometry objects through space and reports any objects in the
			/// scene which intersect. Apart from the number of objects intersected in this way, and the objects
			/// intersected, information on the closest intersection is put in an PxSweepHit structure which can
			/// be processed in the callback. See PxSweepHit.
			/// </summary>
			/// <param name="batchQuery">The scene query object to process the query.</param>
			/// <param name="unitDirection">Normalized direction of the sweep.  </param>
			/// <param name="distance">Sweep distance. Needs to be larger than 0.  </param>
			/// <param name="filterFlags">Choose if to sweep against static, dynamic or both types of objects, or other filter logic. See PxSceneQueryFilterFlags.  </param>
			void LinearSweepSingle(BatchQuery^ batchQuery, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags);

			/// <summary>
			/// Performs a linear sweep through space with the body's geometry objects.
			/// Supported geometries are: PxBoxGeometry, PxSphereGeometry, PxCapsuleGeometry. Other geometry types
			/// will be ignored.
			/// Internally this call is mapped to PxBatchQuery::linearCompoundGeometrySweepSingle().
			/// The function sweeps all specified geometry objects through space and reports any objects in the
			/// scene which intersect. Apart from the number of objects intersected in this way, and the objects
			/// intersected, information on the closest intersection is put in an PxSweepHit structure which can
			/// be processed in the callback. See PxSweepHit.
			/// </summary>
			/// <param name="batchQuery">The scene query object to process the query.</param>
			/// <param name="unitDirection">Normalized direction of the sweep.  </param>
			/// <param name="distance">Sweep distance. Needs to be larger than 0.  </param>
			/// <param name="filterFlags">Choose if to sweep against static, dynamic or both types of objects, or other filter logic. See PxSceneQueryFilterFlags.  </param>
			/// <param name="useShapeFilterData">True if the filter data of the body shapes should be used for the query. False if no filtering is needed or separate filter data is provided.  </param>
			/// <param name="filterDataList">Custom filter data to use for each geometry object of the body. Only considered if useShapeFilterData is false.</param>
			/// <param name="filterDataCount">Number of filter data entries.</param>
			/*/// <param name="userData">The user can assign this to a value of his choice, usually to identify this particular query.</param>*/
			/// <param name="sweepCache">Sweep cache to use with the query.</param>
			void LinearSweepSingle(BatchQuery^ batchQuery, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, bool useShapeFilterData, array<FilterData>^ filterData, SweepCache^ sweepCache);

			/// <summary>
			/// Performs a linear sweep through space with the body's geometry objects, returning all overlaps.
			/// Note: Supported geometries are: PxBoxGeometry, PxSphereGeometry, PxCapsuleGeometry. Other geometry types will be ignored.
			/// Internally this call is mapped to PxBatchQuery::linearCompoundGeometrySweepMultiple().
			/// The function sweeps all geometry objects of the body through space and reports all objects in the scene which intersect. Apart from the number of objects intersected in this way, and the objects intersected, information on the closest intersection is put in an PxSweepHit structure which can be processed in the callback. See PxSweepHit.
			/// </summary>
			/// <param name="batchQuery">The scene query object to process the query.</param>
			/// <param name="unitDirection">Normalized direction of the sweep.  </param>
			/// <param name="distance">Sweep distance. Needs to be larger than 0.  </param>
			/// <param name="filterFlags">Choose if to sweep against static, dynamic or both types of objects, or other filter logic. See PxSceneQueryFilterFlags.  </param>
			void LinearSweepMultiple(BatchQuery^ batchQuery, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags);
			/// <summary>
			/// Performs a linear sweep through space with the body's geometry objects, returning all overlaps.
			/// Note: Supported geometries are: PxBoxGeometry, PxSphereGeometry, PxCapsuleGeometry. Other geometry types will be ignored.
			/// Internally this call is mapped to PxBatchQuery::linearCompoundGeometrySweepMultiple().
			/// The function sweeps all geometry objects of the body through space and reports all objects in the scene which intersect. Apart from the number of objects intersected in this way, and the objects intersected, information on the closest intersection is put in an PxSweepHit structure which can be processed in the callback. See PxSweepHit.
			/// </summary>
			/// <param name="batchQuery">The scene query object to process the query.</param>
			/// <param name="unitDirection">Normalized direction of the sweep.  </param>
			/// <param name="distance">Sweep distance. Needs to be larger than 0.  </param>
			/// <param name="filterFlags">Choose if to sweep against static, dynamic or both types of objects, or other filter logic. See PxSceneQueryFilterFlags.  </param>
			/// <param name="useShapeFilterData">True if the filter data of the body shapes should be used for the query. False if no filtering is needed or separate filter data is provided.  </param>
			/// <param name="filterDataList">Custom filter data to use for each geometry object of the body. Only considered if useShapeFilterData is false.</param>
			/// <param name="filterDataCount">Number of filter data entries.</param>
			/*/// <param name="userData">The user can assign this to a value of his choice, usually to identify this particular query.</param>*/
			/// <param name="sweepCache">Sweep cache to use with the query.</param>
			void LinearSweepMultiple(BatchQuery^ batchQuery, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, bool useShapeFilterData, array<FilterData>^ filterDataList, SweepCache^ sweepCache);

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