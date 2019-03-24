#pragma once

#include "SceneEnum.h"
#include "QueryFilterData.h"
#include "ActorEnum.h"
#include "DominanceGroupPair.h"
#include "JointEnum.h"
#include "PhysicsEnum.h"
#include "RenderBuffer.h"

namespace PhysX
{
	ref class SceneDesc;
	value class Bounds3;
	ref class QueryHit;
	ref class Shape;
	ref class Geometry;
	ref class Actor;
	ref class Physics;
	ref class ControllerManager;
	ref class RaycastHit;
	ref class Joint;
	ref class RigidActor;
	ref class SimulationStatistics;
	ref class Articulation;
	ref class Aggregate;
	ref class SweepHit;
	ref class SceneSweepOperationObject;
	ref class RenderBuffer;
	ref class SweepCache;
	ref class SimulationEventCallback;
	ref class QueryFilterCallback;
	ref class QueryCache;
	ref class OverlapHit;
	ref class Collection;
	ref class SceneLimits;
	ref class ContactModifyCallback;
	ref class RigidDynamic;
	ref class RigidStatic;
	ref class BroadPhaseCallback;
	ref class SimulationFilterCallback;

	/// <summary>
	/// A scene is a collection of bodies, deformables, particle systems and constraints which can interact.
	/// </summary>
	public ref class Scene : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxScene* _scene;

			Physics^ _physics;
			PhysX::ContactModifyCallback^ _contactModifyCallback;
			PhysX::BroadPhaseCallback^ _broadPhaseCallback;
			PhysX::SimulationFilterCallback^ _simulationFilterCallback;

		internal:
			Scene(PxScene* scene, PhysX::Physics^ physics,
				PhysX::BroadPhaseCallback^ broadPhaseCallback,
				PhysX::SimulationFilterCallback^ simulationFilterCallback);
		public:
			~Scene();
		protected:
			!Scene();
			
		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Sets a scene flag. You can only set one flag at a time.
			/// Only the below flags are mutable. Trying to change the others will result in an error:
			/// SceneFlag.SweptIntegration
			/// </summary>
			void SetFlag(SceneFlag flag, bool value);

			//

			/// <summary>
			/// Gets the parent Physics instance.
			/// </summary>
			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}

			/// <summary>
			/// Retrieves the render buffer.
			/// This will contain the results of any active visualization for this scene.
			/// Note: Do not use this method while the simulation is running. Calls to this method while result in undefined behaviour.
			/// </summary>
			RenderBuffer^ GetRenderBuffer([Optional] Nullable<RenderBufferDataFlags> flags);

			/// <summary>Call this method to retrieve statistics for the current simulation step.</summary>
			SimulationStatistics^ GetSimulationStatistics();

			/// <summary>
			/// Returns the wake counter reset value.
			/// </summary>
			property float WakeCounterResetValue
			{
				float get();
			}

			/// <summary>
			/// Shift the scene origin by the specified vector. 
			///
			/// The poses of all objects in the scene and the corresponding data structures will get adjusted to reflect the new origin location (the shift vector will get subtracted from all object positions).
			/// 
			/// Note:
			/// It is the user's responsibility to keep track of the summed total origin shift and adjust all input/output to/from PhysX accordingly.
			/// Do not use this method while the simulation is running. Calls to this method while the simulation is running will be ignored.
			/// 
			/// Make sure to propagate the origin shift to other dependent modules (for example, the character controller module etc.).
			/// 
			/// This is an expensive operation and we recommend to use it only in the case where distance related precision issues may arise in areas far from the origin.
			/// </summary>
			void ShiftOrigin(Vector3 shift);

			#pragma region Actors
			/// <summary>
			/// Retrieve an array of all the actors of certain types in the scene.
			/// </summary>
			IReadOnlyList<Actor^>^ GetActors(ActorTypeFlag types);

			property array<RigidDynamic^>^ RigidDynamicActors
			{
				array<RigidDynamic^>^ get();
			}
			property array<RigidStatic^>^ RigidStaticActors
			{
				array<RigidStatic^>^ get();
			}

			/// <summary>
			/// Retrieve the number of actors of certain types in the scene.
			/// </summary>
			int GetNumberOfActors(ActorTypeFlag types);

			/// <summary>
			/// Adds an actor to this scene.
			/// </summary>
			/// <param name="actor">Actor to add to scene.</param>
			void AddActor(Actor^ actor);
			/// <summary>
			/// Removes an actor from this scene.
			/// </summary>
			/// <param name="actor">Actor to remove from scene.</param>
			void RemoveActor(Actor^ actor);

			/// <summary>Gets the articulations.</summary>
			property array<Articulation^>^ Articulations
			{
				array<Articulation^>^ get();
			}
			#pragma endregion

			#pragma region Joints
			/// <summary>
			/// Creates a joint.
			/// </summary>
			/// <param name="type">The type of the joint.</param>
			/// <param name="actor0">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
			/// <param name="">The position and orientation of the joint relative to actor0.</param>
			/// <param name="actor1">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
			/// <param name="">The position and orientation of the joint relative to actor1.</param>
			/// <returns>A joint of the specified type.</returns>
			Joint^ CreateJoint(JointType type, RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1);

			/// <summary>
			/// Creates a joint.
			/// </summary>
			/// <param name="type">The type of the joint.</param>
			/// <param name="actor0">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
			/// <param name="">The position and orientation of the joint relative to actor0.</param>
			/// <param name="actor1">An actor to which the joint is attached. Null may be used to attach the joint to a specific point in the world frame.</param>
			/// <param name="">The position and orientation of the joint relative to actor1.</param>
			/// <returns>A joint of the specified type.</returns>
			generic<typename T> where T : Joint
			T CreateJoint(RigidActor^ actor0, Matrix localFrame0, RigidActor^ actor1, Matrix localFrame1);
			#pragma endregion

			#pragma region Grouping
			/// <summary>
			/// Samples the dominance matrix.
			/// </summary>
			DominanceGroupPair GetDominanceGroupPair(Byte group1, Byte group2);

			/// <summary>
			/// Specifies the dominance behavior of constraints between two actors with two certain dominance groups.
			/// </summary>
			void SetDominanceGroupPair(Byte group1, Byte group2, DominanceGroupPair dominance);
			#pragma endregion

			#pragma region Simulation
			/// <summary>
			/// Advances the simulation by the specified time.
			/// </summary>
			void Simulate(float elapsedTime);
			/// <summary>
			/// This checks to see if the simulation run has completed.
			/// </summary>
			bool CheckResults([Optional] bool block);
			/// <summary>
			/// 
			/// </summary>
			bool FetchResults([Optional] bool block);
			/// <summary>
			/// Clear internal buffers and free memory.
			/// This method can be used to clear buffers and free internal memory without having
			/// to destroy the scene. Can be useful if the physics data gets streamed in and a checkpoint
			/// with a clean state should be created.
			/// Note:
			/// It is not allowed to call this method while the simulation is running. The call will fail.
			/// </summary>
			void FlushSimulation([Optional] bool sendPendingReports);
			#pragma endregion

			/// <summary>
			/// Gets or sets the number of actors required to spawn a separate rigid body solver thread.
			/// </summary>
			property int SolverBatchSize
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets or sets the current gravity setting.
			/// </summary>
			property Vector3 Gravity
			{
				Vector3 get();
				void set(Vector3 value);
			}

			#pragma region Visualization
			/// <summary>
			/// Function that lets you query debug visualization parameters.
			/// </summary>
			float GetVisualizationParameter(VisualizationParameter param);
			/// <summary>
			/// Function that lets you set debug visualization parameters. 
			/// </summary>
			bool SetVisualizationParameter(VisualizationParameter param, float value);
			/// <summary>
			/// Function that lets you set debug visualization parameters. 
			/// </summary>
			bool SetVisualizationParameter(VisualizationParameter param, bool value);

			property Bounds3 VisualizationCullingBox
			{
				Bounds3 get();
				void set(Bounds3 value);
			}
			#pragma endregion

			#pragma region Raycast, Overlap and Sweep testing
			bool Raycast(Vector3 origin, Vector3 direction, float distance, int maximumHits, Func<array<RaycastHit^>^, bool>^ hitCall, [Optional] HitFlag hitFlag, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCallback, [Optional] QueryCache^ cache);
			bool Sweep(Geometry^ geometry, Matrix pose, Vector3 direction, float distance, int maximumHits, Func<array<SweepHit^>^, bool>^ hitCall, [Optional] HitFlag hitFlag, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCallback, [Optional] QueryCache^ cache);
			bool Overlap(Geometry^ geometry, Matrix pose, int maximumOverlaps, Func<array<OverlapHit^>^, bool>^ hitCall, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCallback);
			#pragma endregion

			#pragma region Character
			ControllerManager^ CreateControllerManager();
			#pragma endregion

			#pragma region Articulation and Aggregate
			/// <summary>
			/// Adds an articulation to this scene.
			/// </summary>
			void AddArticulation(Articulation^ articulation);

			/// <summary>
			/// Removes an articulation from this scene.
			/// </summary>
			void RemoveArticulation(Articulation^ articulation);

			/// <summary>
			/// Adds an aggregate to this scene.
			/// </summary>
			void AddAggregate(Aggregate^ aggregate);

			/// <summary>
			/// Removes an aggregate from this scene.
			/// </summary>
			void RemoveAggregate(Aggregate^ aggregate);

			/// <summary>
			/// Gets the aggregates.
			/// </summary>
			property array<Aggregate^>^ Aggregates
			{
				array<Aggregate^>^ get();
			}
			#pragma endregion

			#pragma region Collection
			Collection^ CreateCollection();
			#pragma endregion

			/// <summary>
			/// Retrieves the SimulationEventCallback object set with SetSimulationEventCallback().
			/// </summary>
			SimulationEventCallback^ GetSimulationEventCallback();
			/// <summary>
			/// Sets a user notify object which receives special simulation events when they occur.
			/// </summary>
			void SetSimulationEventCallback(SimulationEventCallback^ callback);

			void ResetFiltering(Actor^ actor);
			void ResetFiltering(RigidActor^ actor, array<Shape^>^ shapes);

			/// <summary>
			/// Reserves a new client ID.
			/// PX_DEFAULT_CLIENT is always available as the default clientID. Additional clients are returned by this function.
			/// Clients cannot be released once created. An error is reported when more than a supported number of clients (currently 128)
			/// are created. 
			/// </summary>
			int CreateClient();

			/// <summary>
			/// Gets or sets the rebuild rate of the dynamic tree pruning structure.
			/// </summary>
			property int DynamicTreeRebuildRateHint
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets the scene's internal timestamp, increased each time a simulation step is completed.
			/// </summary>
			property int Timestamp
			{
				int get();
			}

			/// <summary>
			/// 
			/// </summary>
			property PhysX::FrictionType FrictionType
			{
				PhysX::FrictionType get();
				void set(PhysX::FrictionType value);
			}

			//

			/// <summary>
			/// Get or sets the scene flags.
			/// </summary>
			property SceneFlag Flags
			{
				SceneFlag get();
			}

			property PhysX::SceneQueryUpdateMode SceneQueryUpdateMode
			{
				PhysX::SceneQueryUpdateMode get();
				void set(PhysX::SceneQueryUpdateMode value);
			}

			/// <summary>
			/// Retrieves the scene's internal scene query timestamp, increased each time a change to the static scene query structure is performed.
			/// </summary>
			property int SceneQueryStaticTimestamp
			{
				int get();
			}

			property PhysX::SceneLimits^ SceneLimits
			{
				PhysX::SceneLimits^ get();
				void set(PhysX::SceneLimits^ value);
			}

			property PhysX::ContactModifyCallback^ ContactModifyCallback
			{
				PhysX::ContactModifyCallback^ get();
				void set(PhysX::ContactModifyCallback^ value);
			}

			property PhysX::BroadPhaseCallback^ BroadPhaseCallback
			{
				PhysX::BroadPhaseCallback^ get();
				void set(PhysX::BroadPhaseCallback^ value);
			}

			property SimulationFilterCallback^ FilterCallback
			{
				SimulationFilterCallback^ get();
			}

			/// <summary>
			/// Gets or sets an object, usually to create a 1:1 relationship with a user object.
			/// </summary>
			property Object^ UserData;

		internal:
			property PxScene* UnmanagedPointer
			{
				PxScene* get();
			}
	};
};