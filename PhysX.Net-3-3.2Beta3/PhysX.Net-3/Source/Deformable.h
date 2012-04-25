#pragma once

#include "Actor.h"
#include "DeformableEnum.h"

#include <PxDeformable.h> 

namespace PhysX
{
	ref class DeformableDesc;
	ref class DeformableMesh;
	ref class DeformableReadData;
	ref class DeformableConstrainCoefficients;
	value class FilterData;

	public ref class Deformable : Actor
	{
		private:
			PhysX::DeformableMesh^ _deformableMesh;

		internal:
			Deformable(PxDeformable* deformable, PhysX::DeformableMesh^ deformableMesh, PhysX::Physics^ owner);
		public:
			~Deformable();
		protected:
			!Deformable();

		public:
			/// <summary>
			/// Tears the deformable at a given vertex.
			/// For cloth, connected triangles can separate along their edges. For soft bodies,
			/// connected tetrahedra can separate along their faces.
			/// First the vertex is duplicated. The primitive on one side of the split plane keep
			/// the original vertex. For all primitives on the opposite side the original vertex
			/// is replaced by the new one. The split plane is defined by the world location of
			/// the vertex and the normal provided by the user.
			/// </summary>
			/// <param name="vertexId">Index of the vertex to tear.</param>
			/// <param name="normal">The normal of the split plane.</param>
			/// <returns>True if the split had an effect (i.e. there were primitives on both sides of the split plane).</returns>
			bool TearVertex(int vertexId, Vector3 normal);

			/// <summary>Executes a raycast against the deformable.</summary>
			/// <param name="rayOrigin">Origin of the ray in world space.</param>
			/// <param name="rayDirection">Direction of the ray in world space.</param>
			/// <param name="hit">The hit position.</param>
			/// <returns>Index to the nearest vertex hit by the raycast.</returns>
			Nullable<int> Raycast(Vector3 rayOrigin, Vector3 rayDirection, Vector3 hit);

			/// <summary>
			/// Sets the vertex positions of the deformable.
			/// The supplied positions are used to change vertex positions in the order the ids
			/// are listed in the id buffer. Duplicate ids are allowed.
			/// A position buffer of stride zero is allowed. 
			/// </summary>
			void SetPositions(array<Vector3>^ positions, [Optional] array<int>^ indices);

			/// <summary>
			/// Sets the vertex velocities of the deformable.
			/// The supplied positions are used to change vertex positions in the order the ids are
			/// listed in the id buffer. Duplicate ids are allowed.
			/// A velocity buffer of stride zero is allowed.
			/// </summary>
			void SetVelocities(array<Vector3>^ velocities, [Optional] array<int>^ indices);

			/// <summary>
			/// Sets the buffer of constrain positions.
			/// The user can supply a buffer of positions and normals coming from an animation of the
			/// deformable for instance. The simulated vertices are then corrected via the constrain
			/// positions, normals and the constrain coefficiens.
			/// </summary>
			/// <param name="positions">
			/// The user supplied buffer containing all constrain positions for the deformable.
			/// The number of positions provided must correspond to the number returned by NumberOfVertices
			/// </param>
			void SetConstrainPositins(array<Vector3>^ positions);

			/// <summary>
			/// Sets the buffer of constrain normals.
			/// The user can supply a buffer of positions and normals coming from an animation of the
			/// deformable for instance. The simulated vertices are then corrected via the constrain
			/// positions, normals and the constrain coefficiens set by setConstrainCoefficients.
			/// </summary>
			/// <param name="normals">
			/// The user supplied buffer containing all constrain normals for the deformable.
			/// The number of normals provided must correspond to the number returned by NumberOfVertices
			/// </param>
			void SetConstrainNormals(array<Vector3>^ normals);

			/// <summary>
			/// Sets the buffer of constrain coefficients of the type PxReal.
			/// The user can supply a buffer of positions and normals coming from an animation of the deformable
			/// for instance. The simulated vertices are then corrected via the constrain positions, normals
			/// and the constrain coefficiens set by setConstrainCoefficients.
			/// </summary>
			/// <param name="coefficients">
			/// The user supplied buffer containing all constrain coefficients for the deformable.
			/// The number of coefficients provided must correspond to the number returned by NumberOfVertices
			/// </param>
			void SetConstrainCoefficients(array<DeformableConstrainCoefficients^>^ coefficients);

			/// <summary>
			/// Wakes up the deformable if it is sleeping.
			/// The wakeCounterValue determines how long until the deformable is put to sleep, a value of zero means
			/// that the deformable is sleeping.
			/// WakeUp(0) is equivalent to Deformable.PutToSleep().
			/// </summary>
			/// <param name="wakeCounterValue">
			/// New sleep counter value. Range: [0, inf].
			/// </param>
			void WakeUp([Optional] Nullable<float> wakeCounterValue);

			/// <summary>
			/// Forces the deformable to sleep.
			/// The deformable will fall asleep.
			/// </summary>
			void PutToSleep();

			/// <summary>
			/// Marks the object to reset interactions and re-run collision filters in the next simulation step.
			/// </summary>
			void ResetFiltering();

			/// <summary>
			/// Applies forces (or impulses), defined in the global coordinate frame, to a set of deformable vertices.
			/// ForceMode determines if the force is to be conventional or impulsive.
			/// </summary>
			/// <param name="forces">Forces/impulses to add, defined in the global frame. Range: force vector.</param>
			/// <param name="mode">The mode to use when applying the force/impulse.</param>
			/// <param name="indices">
			/// Optional index list of target vertices.
			/// Duplicates are allowed. (see ForceMode, supported modes are ForceMode.Force, ForceMode.Impulse, ForceMode.Acceleration, ForceMode.VelocityChange)
			/// </param>
			void AddForces(array<Vector3>^ forces, ForceMode mode, [Optional] array<int>^ indices);

			/// <summary>
			/// Locks the deformable read data and provides the data descriptor for accessing it.
			/// </summary>
			DeformableReadData^ LockDeformableReadData();

			/// <summary>
			/// Saves the deformable descriptor.
			/// </summary>
			DeformableDesc^ SaveToDesc();

			//

			/// <summary>
			/// Gets or sets the corresponding deformable mesh.
			/// </summary>
			property PhysX::DeformableMesh^ DeformableMesh
			{
				PhysX::DeformableMesh^ get();
			}

			/// <summary>
			/// Gets or sets the bending stiffness in the range from 0 to 1. Ineffective for soft bodies.
			/// </summary>
			property float BendingStiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable volume stiffness in the range from 0 to 1. Ineffective for cloth.
			/// </summary>
			property float VolumeStiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable stretching stiffness in the range from 0 to 1.
			/// </summary>
			property float StretchingStiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the damping coefficient in the range from 0 to 1. 
			/// </summary>
			property float DampingCoefficient
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable static friction coefficient in the range from 0 to +inf.
			/// </summary>
			property float StaticFriction
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable dynamic friction coefficient in the range from 0 to +inf.
			/// </summary>
			property float DynamicFriction
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable pressure coefficient (must be non negative). Ineffective for soft bodies.
			/// </summary>
			property float Pressure
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable tear factor (must be larger than one).
			/// </summary>
			property float TearFactor
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable attachment tear factor (must be larger than one).
			/// </summary>
			property float AttachmentTearFactor
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the deformable mass.
			/// </summary>
			property float Mass
			{
				float get();
			}

			/// <summary>
			/// Gets or sets the relative grid spacing for the broad phase.
			/// The deformable is represented by a set of world aligned cubical cells in broad phase.
			/// The size of these cells is determined by multiplying the length of the diagonal of
			/// the AABB of the initial deformable size with this constant.
			/// </summary>
			property float RelativeGridSpacing
			{
				float get();
			}

			/// <summary>
			/// Gets or sets the deformable solver iterations.
			/// </summary>
			property int SolverIterations
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets or sets the number of iterations of the hierarchical deformable solver.
			/// </summary>
			property int HierarchicalSolverIterations
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets or sets the world space AABB enclosing all deformable points.
			/// </summary>
			property Bounds3 WorldBounds
			{
				Bounds3 get();
			}

			/// <summary>
			/// Gets or sets the valid bounds of the deformable in world space.
			/// </summary>
			property Bounds3 ValidBounds
			{
				Bounds3 get();
				void set(Bounds3 value);
			}

			/// <summary>
			///  Gets the current number of deformable vertices.
			/// </summary>
			property int NumberOfVertices
			{
				int get();
			}

			/// <summary>
			///  Gets the maximum number of deformable vertices.
			/// </summary>
			property int MaximumVertices
			{
				int get();
			}

			/// <summary>
			/// Gets or sets the collision stiffness.
			/// </summary>
			property float CollisionStiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the attachment stiffness.
			/// </summary>
			property float AttachmentStiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the contact offset.
			/// </summary>
			property float ContactOffset
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the rest offset.
			/// </summary>
			property float RestOffset
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the penetration offset.
			/// </summary>
			property float PenetrationOffset
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the self collision offset.
			/// </summary>
			property float SelfCollisionOffset
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the external acceleration which affects all non attached vertices of the deformable.
			/// </summary>
			property Vector3 ExternalAcceleration
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the acceleration acting normal to the deformable surface at each vertex.
			/// </summary>
			property Vector3 WindAcceleration
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets if this deformable is sleeping.
			/// </summary>
			property bool IsSleeping
			{
				bool get();
			}

			/// <summary>
			/// Gets or sets the linear velocity below which a deformable may go to sleep.
			/// </summary>
			property float SleepLinearVelocity
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the user definable collision filter data.
			/// </summary>
			property FilterData SimulationFilterData
			{
				FilterData get();
				void set(FilterData value);
			}

			/// <summary>
			/// Gets or sets the deformable flags.
			/// </summary>
			property DeformableFlag DeformableFlags
			{
				DeformableFlag get();
				void set(DeformableFlag value);
			}

		internal:
			property PxDeformable* UnmanagedPointer
			{
				PxDeformable* get() new;
			}
	};
};