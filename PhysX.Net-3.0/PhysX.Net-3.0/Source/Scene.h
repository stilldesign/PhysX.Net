#pragma once

#include <PxScene.h>
#include "SceneEnum.h"
#include "SceneQueryFilterData.h"
#include "ActorEnum.h"
#include "ConstraintDominance.h"
#include "JointEnum.h"

namespace PhysX
{
	ref class SceneDesc;
	value class Bounds3;
	ref class SceneQueryHit;
	ref class Shape;
	ref class Geometry;
	ref class Actor;
	ref class ActiveTransform;
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
			List<Actor^>^ _actors;
			List<Joint^>^ _joints;
			List<Aggregate^>^ _aggregates;
			List<Articulation^>^ _articulations;
			List<ControllerManager^>^ _controllerManagers;

		internal:
			Scene(PxScene* scene, PhysX::Physics^ physics);
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
			/// Saves the scene descriptor.
			/// </summary>
			/// <returns>
			/// A scene description or null if the save failed.
			/// </returns>
			SceneDesc^ SaveToDesc();
			
			//

			/// <summary>
			/// Gets the parent Physics instance.
			/// </summary>
			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}

			/// <summary>Call this method to retrieve statistics for the current simulation step.</summary>
			SimulationStatistics^ GetSimulationStatistics();

			#pragma region Actors
			/// <summary>
			/// Retrieve an array of all the actors of certain types in the scene.
			/// </summary>
			property IEnumerable<Actor^>^ Actors
			{
				IEnumerable<Actor^>^ get();
			}

			/// <summary>
			/// Retrieve the number of actors of certain types in the scene.
			/// </summary>
			int GetNumberOfActors(ActorTypeSelectionFlag types);

			/// <summary>
			/// Queries the PxScene for a list of the PxActors whose transforms have been updated during the previous simulation step.
			/// </summary>
			array<ActiveTransform^>^ GetActiveTransforms([Optional] Nullable<int> clientId);

			/// <summary>
			/// Adds an actor to this scene.
			/// </summary>
			/// <param name="actor">Actor to add to scene.</param>
			/// <returns>
			/// True on success.
			/// </returns>
			bool AddActor(Actor^ actor);
			/// <summary>
			/// Removes an actor from this scene.
			/// </summary>
			/// <param name="actor">Actor to remove from scene.</param>
			/// <returns>
			/// True on success.
			/// </returns>
			bool RemoveActor(Actor^ actor);

			/// <summary>Gets the articulations.</summary>
			property IEnumerable<Articulation^>^ Articulations
			{
				IEnumerable<Articulation^>^ get();
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
			ConstraintDominance GetDominanceGroupPair (Byte group1, Byte group2);

			/// <summary>
			/// Specifies the dominance behavior of constraints between two actors with two certain dominance groups.
			/// </summary>
			void SetDominanceGroupPair(Byte group1, Byte group2, ConstraintDominance dominance);
			#pragma endregion

			#pragma region Simulation
			/// <summary>
			/// Advances the simulation by an elapsedTime time.
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
			/// </summary>
			void Flush([Optional] bool sendPendingReports);
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

			property Bounds3 VisualizationCullingBox
			{
				Bounds3 get();
				void set(Bounds3 value);
			}
			#pragma endregion

			#pragma region Raycast
			/// <summary>
			/// Raycast returning any blocking hit, not necessarily the closest.
			/// Returns whether any rigid actor is hit along the ray.
			/// </summary>
			/// <param name="origin">Origin of the ray.</param>
			/// <param name="direction">Normalized direction of the ray.</param>
			/// <param name="distance">Length of the ray. Needs to be larger than 0.</param>
			/// <param name="filterData">Filtering data and simple logic.</param>
			/// <returns>Raycast hit information, or null if no hit occured.</returns>
			SceneQueryHit^ RaycastAny(Vector3 origin, Vector3 direction, float distance, [Optional] Nullable<SceneQueryFilterData> filterData);

			/// <summary>
			/// Raycast returning a single result.
			/// Returns the first rigid actor that is hit along the ray. Data for a blocking hit will be returned as
			/// specified by the outputFlags field. Touching hits will be ignored.
			/// </summary>
			/// <param name="origin">Origin of the ray.</param>
			/// <param name="direction">Normalized direction of the ray.</param>
			/// <param name="distance">Length of the ray. Needs to be larger than 0.</param>
			/// <param name="filterData">Filtering data and simple logic.</param>
			/// <returns>Raycast hit information, or null if no hit occured.</returns>
			RaycastHit^ RaycastSingle(Vector3 origin, Vector3 direction, float distance, [Optional] Nullable<SceneQueryFlags> outputFlags, [Optional] Nullable<SceneQueryFilterData> filterData);

			/// <summary>
			/// Raycast returning multiple results.
			/// Find all rigid actors that get hit along the ray. Each result contains data as specified by the outputFlags field.
			/// </summary>
			/// <param name="origin">Origin of the ray.</param>
			/// <param name="direction">Normalized direction of the ray.</param>
			/// <param name="distance">Length of the ray. Needs to be larger than 0.</param>
			/// <param name="filterData">Filtering data and simple logic.</param>
			/// <returns>Raycast hit information, or null if no hit occured.</returns>
			array<RaycastHit^>^ RaycastMultiple(Vector3 origin, Vector3 direction, float distance, SceneQueryFlags outputFlags, int hitBufferSize, [Optional] Nullable<SceneQueryFilterData> filterData);
			#pragma endregion

			#pragma region Sweep
			/// <summary>
			/// Sweep returning any blocking hit, not necessarily the closest.
			/// Returns whether any rigid actor is hit along the sweep path.
			/// </summary>
			/// <param name="geometry">Geometry of object to check for overlap (supported types are: box, sphere, capsule).</param>
			/// <param name="pose">Pose of the sweep object.</param>
			/// <param name="direction">Normalized direction of the ray.</param>
			/// <param name="distance">Length of the ray. Needs to be larger than 0.</param>
			/// <param name="queryFlags">Lets the user filter out initially overlapping objects, if necessary.</param>
			/// <param name="filterData">Filtering data and simple logic.</param>
			/// <returns>A hit result object, or null if no hit occured.</returns>
			SceneQueryHit^ SweepAny(Geometry^ geometry, Matrix pose, Vector3 direction, float distance, SceneQueryFlags queryFlags, [Optional] Nullable<SceneQueryFilterData> filterData);

			/// <summary>
			/// Sweep returning any blocking hit, not necessarily the closest.
			/// Returns whether any rigid actor is hit along the sweep path.
			/// </summary>
			/// <param name="objects">Geometry, transforms and filtering of objects to check for overlap (supported types are: box, sphere, capsule).</param>
			/// <param name="direction">Normalized direction of the ray.</param>
			/// <param name="distance">Length of the ray. Needs to be larger than 0.</param>
			/// <param name="outputFlags">Specifies which properties should be written to the hit information.</param>
			/// <param name="maxNumberOfHits>Maximum number of hits.</param>
			/// <param name="filterFlags">Simple filter logic.</param>
			/// <returns>A hit result object, or null if no hit occured.</returns>
			array<SweepHit^>^ SweepMultiple(array<SceneSweepOperationObject^>^ objects, Vector3 direction, float distance, SceneQueryFlags outputFlags, int maxNumberOfHits, Nullable<SceneQueryFilterFlag> filterFlags);
			#pragma endregion

			#pragma region Overlap
			/// <summary>
			/// Test returning, for a given geometry, any overlapping object in the scene.
			/// </summary>
			/// <param name="geometry">Geometry of object to check for overlap (supported types are: box, sphere, capsule).</param>
			/// <param name="pose">Pose of the object.</param>
			/// <param name="filterData">Filtering data and simple logic.</param>
			/// <returns>The overlapping shape, or null if no overlap occured.</returns>
			Shape^ OverlapAny(Geometry^ geometry, Matrix pose, [Optional] Nullable<SceneQueryFilterData> filterData);

			/// <summary>
			/// Test overlap between a geometry and objects in the scene.
			/// </summary>
			/// <param name="geometry">Geometry of object to check for overlap (supported types are: box, sphere, capsule).</param>
			/// <param name="pose">Pose of the object.</param>
			/// <param name="filterData">Filtering data and simple logic.</param>
			/// <returns>An array of overlapping shapes.</returns>
			array<Shape^>^ OverlapMultiple(Geometry^ geometry, Matrix pose, [Optional] Nullable<int> hitLimit, [Optional] Nullable<SceneQueryFilterData> filterData);
			#pragma endregion

			#pragma region Character
			ControllerManager^ CreateControllerManager();
			#pragma endregion

			#pragma region Articulation and Aggregate
			/// <summary>
			/// Adds an articulation to this scene.
			/// </summary>
			bool AddArticulation(Articulation^ articulation);

			/// <summary>
			/// Removes an articulation from this scene.
			/// </summary>
			bool RemoveArticulation(Articulation^ articulation);

			/// <summary>
			/// Adds an aggregate to this scene.
			/// </summary>
			bool AddAggregate(Aggregate^ aggregate);

			/// <summary>
			/// Removes an aggregate from this scene.
			/// </summary>
			bool RemoveAggregate(Aggregate^ aggregate);

			/// <summary>Gets the aggregates.</summary>
			property IEnumerable<Aggregate^>^ Aggregates
			{
				IEnumerable<Aggregate^>^ get();
			}
			#pragma endregion

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

			//

			/// <summary>
			/// Get or sets the scene flags.
			/// </summary>
			property SceneFlag Flags
			{
				SceneFlag get();
				void set(SceneFlag value);
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