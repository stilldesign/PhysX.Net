#pragma once

#include "Actor.h"
#include "RigidBody.h"

namespace PhysX
{
	value class SolverIterationCounts;

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
			void WakeUp([Optional] Nullable<float> wakeCounterValue);

			/// <summary>
			/// Forces the actor to sleep.
			/// </summary>
			void PutToSleep();

			RigidDynamic^ CloneDynamic(Matrix transform);

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
			/// Gets or sets the mass-normalized kinetic energy threshold below which an actor may go to sleep.
			/// </summary>
			property float SleepThreshold
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
			/// Gets or sets the dynamic rigid body flags.
			/// </summary>
			property RigidDynamicFlags Flags
			{
				RigidDynamicFlags get();
				void set(RigidDynamicFlags value);
			}

		internal:
			property PxRigidDynamic* UnmanagedPointer
			{
				PxRigidDynamic* get();
			}
	};
};