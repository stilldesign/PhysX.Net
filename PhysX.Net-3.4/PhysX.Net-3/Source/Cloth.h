#pragma once

#include "Actor.h"
#include "Physics.h"
#include "ClothParticle.h"
#include "ClothParticleMotionConstraint.h"
#include "ClothMotionConstraintConfig.h"
#include "ClothParticleSeparationConstraint.h"
#include "ClothEnum.h"
#include "ClothCollisionSphere.h"
#include "ClothCollisionPlane.h"
#include "Bounds3.h"
#include "PhysicsEnum.h"

namespace PhysX
{
	ref class ClothFabric;
	ref class ClothParticleData;
	ref class ClothTetherConfig;

	public ref class Cloth : Actor
	{
	private:
		PhysX::ClothFabric^ _fabric;

	public:
		Cloth(PxCloth* cloth, PhysX::Physics^ owner);

	public:
		/// <summary>
		/// Updates cloth particle location or inverse weight for current and previous particle state.
		/// Note: The invWeight stored in currentParticles is the new particle inverse mass, or zero for
		/// a static particle. However, the invWeight stored in previousParticles is still used once for
		/// the next particle integration and fabric solve.
		/// If currentParticles or previousParticles are non-null then they must be the length specified by getNbParticles().
		/// This can be used to teleport particles (use same positions for current and previous).
		/// </summary>
		/// <param name="currentParticles">The particle data for the current particle state or null if the state should not be changed.</param>
		/// <param name="previousParticles">The particle data for the previous particle state or null if the state should not be changed.</param>
		void SetParticles(array<ClothParticle>^ currentParticles, array<ClothParticle>^ previousParticles);

		/// <summary>
		/// Copies motion constraints to the user provided buffer.
		/// </summary>
		array<ClothParticleMotionConstraint>^ GetMotionConstraints();
		/// <summary>
		/// Updates motion constraints (position and radius of the constraint sphere).
		/// Note: The motionConstraints must either be null to disable motion constraints, or be the same length as the number of particles, see NumberOfParticles property.
		/// </summary>
		/// <param name="motionConstraints">Motion constraints at the end of the next Simulate() call.</param>
		void SetMotionConstraints(array<ClothParticleMotionConstraint>^ motionConstraints);

		/// <summary>
		/// 
		/// </summary>
		array<ClothParticleSeparationConstraint>^ GetSeparationConstraints();
		/// <summary>
		/// 
		/// </summary>
		void SetSeparationConstraints(array<ClothParticleSeparationConstraint>^ separationConstraints);

		/// <summary>
		/// Assign current to previous positions for collision shapes, motion constraints, and separation constraints.
		/// </summary>
		void ClearInterpolation();

		// TODO: Do these really need Vector4 or just Vector3?
		array<Vector4>^ GetParticleAccelerations();
		array<Vector3>^ GetParticleAccelerations3();
		void SetParticleAccelerations(array<Vector4>^ particleAccelerations);
		void SetParticleAccelerations(array<Vector3>^ particleAccelerations);

		/// <summary>
		/// Updates location and radii of collision spheres.
		/// </summary>
		void SetCollisionSpheres(array<ClothCollisionSphere>^ spheres);

		/// <summary>
		/// Adds a collision plane.
		/// </summary>
		void AddCollisionPlane(ClothCollisionPlane plane);
		/// <summary>
		/// Removes a collision plane.
		/// Note: The indices of planes added after index are decremented by 1.
		/// Convexes that reference the plane will have the plane removed from their mask. If after removal
		/// a convex consists of zero planes, it will also be removed. 
		/// <param name="index">Index of plane to remove.</param>
		/// </summary>
		void RemoveCollisionPlane(int index);
		/// <summary>
		/// Updates positions of collision planes.
		/// </summary>
		void SetCollisionPlanes(array<ClothCollisionPlane>^ planes);

		/// <summary>
		/// Adds a new collision convex.
		/// A collision convex is defined as the intersection of planes. 
		/// </summary>
		/// <param name="mask">The bitmask of the planes that make up the convex.</param>
		void AddCollisionConvex(int mask);
		/// <summary>
		/// Removes a collision convex.
		/// Note: The indices of convexes added after index are decremented by 1.
		/// Planes referenced by this convex will not be removed.
		/// </summary>
		/// <param name="index">Index of convex to remove.</param>
		void RemoveCollisionConvex(int index);

		/// <summary>
		/// Assigns virtual particles.
		/// Virtual particles provide more robust and accurate collision handling against collision spheres
		/// and capsules. More virtual particles will generally increase the accuracy of collision handling,
		/// and thus a sufficient number of virtual particles can mimic triangle-based collision handling.
		/// Virtual particles are specified as barycentric interpolation of real particles: The position of a
		/// virtual particle is w0 * P0 + w1 * P1 + w2 * P2, where P1, P2, P3 real particle positions.
		/// The barycentric weights w0, w1, w2 are stored in a separate table so they can be shared across multiple
		/// virtual particles. 
		/// </summary>
		/// <param name="triangleVertexAndWeightIndices">Each virtual particle has four indices, the first three for real particle indices, and the last for the weight table index. Thus, the length of indices needs to be 4*numVirtualParticles.</param>
		/// <param name="triangleVertexWeightTable">Array for barycentric weights.</param>
		void SetVirtualParticles(array<int>^ triangleVertexAndWeightIndices, array<Vector3>^ triangleVertexWeightTable);

		/// <summary>
		/// Gets the array virtual particles.
		/// </summary>
		array<int>^ GetVirtualParticles();

		/// <summary>
		/// Gets an array of weight table values of the virtual particles.
		/// </summary>
		array<Vector3>^ GetVirtualParticleWeights();

		/// <summary>
		/// Sets the target pose.
		/// This function will move the cloth in world space. The resulting simulation may reflect inertia
		/// effect as a result of pose acceleration.
		/// </summary>
		/// <param name="pose">Target pose at the end of the next simulate() call.</param>
		void SetTargetPose(Matrix pose);
		
		void WakeUp();

		void PutToSleep();

		/// <summary>
		/// Locks the cloth solver so that external applications can safely read back particle data.
		/// </summary>
		ClothParticleData^ LockParticleData();
		/// <summary>
		/// Locks the cloth solver so that external applications can safely read back particle data.
		/// </summary>
		ClothParticleData^ LockParticleData(DataAccessFlag flag);

		void SetInertiaScale(float scale);

		/// <summary>
		/// Returns world space bounding box.
		/// </summary>
		/// <returns>Particle bounds in global coordinates.</returns>
		Bounds3 GetWorldBounds();

		void SetDragCoefficient(PxReal scale);

		//

		/// <summary>
		/// Gets the corresponding cloth fabric.
		/// </summary>
		property PhysX::ClothFabric^ Fabric
		{
			PhysX::ClothFabric^ get();
		}

		/// <summary>
		/// Returns the number of particles.
		/// </summary>
		property int NumberOfParticles
		{
			int get();
		}
		/// <summary>
		/// Returns the number of motion constraints.
		/// </summary>
		property int NumberOfMotionConstraints
		{
			int get();
		}
		
		/// <summary>
		/// Gets the number of separation constraints.
		/// </summary>
		property int NumberOfSeparationConstraints
		{
			int get();
		}

		/// <summary>
		/// Returns the number of particle accelerations.
		/// </summary>
		property int NumberOfParticleAccelerations
		{
			int get();
		}

		/// <summary>
		/// Returns the number of collision spheres.
		/// </summary>
		property int NumberOfCollisionSpheres
		{
			int get();
		}

		///// <summary>
		///// Returns the number of collision capsules.
		///// </summary>
		//property int NumberOfCollisionSpherePairs
		//{
		//	int get();
		//}

		/// <summary>
		/// Returns the number of collision planes.
		/// </summary>
		property int NumberOfCollisionPlanes
		{
			int get();
		}

		/// <summary>
		/// Returns the number of collision convexes.
		/// </summary>
		property int NumberOfCollisionConvexes
		{
			int get();
		}

		/// <summary>
		/// Returns the number of virtual particles.
		/// </summary>
		property int NumberOfVirtualParticles
		{
			int get();
		}

		/// <summary>
		/// Returns the number of the virtual particle weights.
		/// </summary>
		property int NumberOfVirtualParticleWeights
		{
			int get();
		}

		/// <summary>
		/// Gets or sets the global pose.
		/// </summary>
		property Matrix GlobalPose
		{
			Matrix get();
			void set(Matrix value);
		}

		property Vector3 WindVelocity
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property float WindDrag
		{
			float get();
			void set(float value);
		}
		property float WindLift
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Gets or sets external particle accelerations.
		/// Note: Use this to implement simple wind etc.
		/// </summary>
		/// <param name="acceleration">New acceleration in global coordinates (default: 0.0).</param>
		property Vector3 ExternalAcceleration
		{
			Vector3 get();
			void set(Vector3 value);
		}

		/// <summary>
		/// Sets the damping coefficient.
		/// The damping coefficient is the portion of local particle velocity that is canceled in 1/10 sec.
		/// </summary>
		/// <param name="dampingCoefficient">New damping coefficient between 0.0 and 1.0 (default: 0.0).</param>
		property Vector3 DampingCoefficient
		{
			Vector3 get();
			void set(Vector3 value);
		}

		/// <summary>
		/// Gets or set the collision friction coefficient.
		/// Note: Currently only spheres and capsules impose friction on the colliding particles.
		/// New friction coefficient between 0.0 and 1.0 (default: 0.0).
		/// </summary>
		property float FrictionCoefficient
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Gets or sets the linear drag coefficient.
		/// The linear drag coefficient is the portion of the pose translation that is applied to each particle per stiffness period (see PxCloth::setStiffnessFrequency).
		/// 
		/// The scale is specified independently for each local space axis. 
		/// Linear drag coefficient between 0.0f and 1.0 (default: 0.0).  
		/// The drag coefficient shouldn't be set higher than the damping coefficient. 
		/// </summary>
		property Vector3 LinearDragCoefficient
		{
			Vector3 get();
			void set(Vector3 value);
		}

		/// <summary>
		/// Gets or sets the angular drag coefficient.
		/// The angular drag coefficient is the portion of the pose rotation that is applied to each particle per stiffness period (see PxCloth::setStiffnessFrequency). 
		/// The scale is specified independently for each local rotation axis. 
		/// New angular drag coefficient between 0.0f and 1.0 (default: 0.0).  
		/// The drag coefficient shouldn't be set higher than the damping coefficient. 
		/// </summary>
		property Vector3 AngularDragCoefficient
		{
			Vector3 get();
			void set(Vector3 value);
		}

		/// <summary>
		/// Gets or sets the collision mass scaling coefficient.
		/// During collision it is possible to artificially increase the mass of a colliding particle, this has
		/// an effect comparable to making constraints attached to the particle stiffer and can help reduce
		/// stretching and interpenetration around collision shapes.
		/// Unitless multiplier that can take on values > 1 (default: 0.0).
		/// </summary>
		property float CollisionMassScale
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Gets or sets the solver frequency parameter per second.
		/// Solver frequency specifies how often the simulation step is computed per second. For example, a
		/// value of 60 represents one simulation step per frame in a 60fps scene. A value of 120 will
		/// represent two simulation steps per frame, etc.
		/// </summary>
		property float SolverFrequency
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Gets or sets cloth flags (e.g. use GPU or not, use CCD or not).
		/// </summary>
		property ClothFlag Flags
		{
			ClothFlag get();
			void set(ClothFlag value);
		}

		/// <summary>
		/// Returns true if cloth is in sleep state.
		/// </summary>
		property bool IsSleeping
		{
			bool get();
		}

		/// <summary>
		/// 
		/// </summary>
		property float SleepLinearVelocity
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Returns previous time step size.
		/// Time between sampling of previous and current particle positions for computing particle velocity.
		/// </summary>
		property float PreviousTimestep
		{
			float get();
		}

		/// <summary>
		/// Gets or sets the stiffness frequency parameter.
		/// </summary>
		property float StiffnessFrequency
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// 
		/// </summary>
		property ClothMotionConstraintConfig MotionConstraintConfig
		{
			ClothMotionConstraintConfig get();
			void set(ClothMotionConstraintConfig value);
		}

		property Vector3 LinearInertiaScale
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property Vector3 AngularInertiaScale
		{
			Vector3 get();
			void set(Vector3 value);
		}
		property Vector3 CentrifugalInertiaScale
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property ClothTetherConfig^ TetherConfig
		{
			ClothTetherConfig^ get();
			void set(ClothTetherConfig^ value);
		}

	internal:
		property PxCloth* UnmanagedPointer
		{
			PxCloth* get();
		}
	};
};