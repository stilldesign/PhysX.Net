#pragma once

#include "Actor.h"
#include "RigidBody.h"

namespace PhysX
{
	value class SolverIterationCounts;
	ref class Physics;

	/// <summary>
	/// RigidDynamic represents a dynamic rigid simulation object in the physics SDK.
	/// </summary>
	public ref class RigidDynamic : RigidBody
	{
		internal:
			RigidDynamic(PxRigidDynamic* rigidDynamic, PhysX::IDisposable^ owner);

		public:
			/// <summary>
			/// Get target pose of a kinematically controlled dynamic actor.
			/// </summary>
			Nullable<Matrix> GetKinematicTarget();
			/// <summary>
			/// Moves kinematically controlled dynamic actors through the game world.
			/// </summary>
			void SetKinematicTarget(Matrix destination);

			/// <summary>
			/// Wakes up the actor if it is sleeping.
			/// </summary>
			void WakeUp();

			/// <summary>
			/// Forces the actor to sleep.
			/// </summary>
			void PutToSleep();

			/// <summary>
			/// Clones the Rigid Dynamic into the same Physics. This Rigid Dynamic have been added to a Scene.
			/// </summary>
			RigidDynamic^ CloneDynamic(Matrix transform);
			/// <summary>
			/// Clones the Rigid Dynamic.
			/// </summary>
			RigidDynamic^ CloneDynamic(Matrix transform, PhysX::Physics^ physics);

			//

			/// <summary>
			/// Gets or sets the linear damping coefficient.
			/// </summary>
			property float LinearDamping
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the angular damping coefficient.
			/// </summary>
			property float AngularDamping
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the maximum angular velocity permitted for this actor. 
			/// </summary>
			property float MaxAngularVelocity
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets whether or not the body is sleeping.
			/// </summary>
			property bool IsSleeping
			{
				bool get();
			}

			/// <summary>
			/// Gets or sets the mass-normalized kinetic energy threshold below which an actor may go to sleep.
			/// </summary>
			property float SleepThreshold
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the mass-normalized kinetic energy below which an actor may participate in stabilization.
			/// </summary>
			property float StabilizationThreshold
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the wake counter of the actor.
			/// </summary>
			property float WakeCounter
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the solver iteration counts for the body.
			/// </summary>
			property PhysX::SolverIterationCounts SolverIterationCounts
			{
				PhysX::SolverIterationCounts get();
				void set(PhysX::SolverIterationCounts value);
			}

			/// <summary>
			/// Gets or sets the force threshold for contact reports.
			/// </summary>
			property float ContactReportThreshold
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the rigid dynamic lock flags.
			/// </summary>
			property PhysX::RigidDynamicLockFlags RigidDynamicLockFlags
			{
				PhysX::RigidDynamicLockFlags get();
				void set(PhysX::RigidDynamicLockFlags value);
			}

		internal:
			property PxRigidDynamic* UnmanagedPointer
			{
				PxRigidDynamic* get();
			}
	};
};