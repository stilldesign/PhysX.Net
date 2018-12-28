#pragma once

namespace PhysX
{
	ref class Scene;
	ref class Actor;
	ref class Articulation;
	ref class Serializable;
	ref class Physics;

	/// <summary>
	/// Class to aggregate actors into a single broad phase entry.
	/// </summary>
	public ref class Aggregate : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxAggregate* _aggregate;

		internal:
			Aggregate(PxAggregate* aggregate, PhysX::Physics^ owner);
		public:
			~Aggregate();
		protected:
			!Aggregate();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Adds an actor to the aggregate object.
			/// A warning is output if the total number of actors is reached, or if the incoming actor already belongs to an aggregate.
			/// If the aggregate belongs to a scene, adding an actor to the aggregate also adds the actor to that scene.
			/// If the actor already belongs to a scene, a warning is output and the call is ignored. You need to remove the
			/// actor from the scene first, before adding it to the aggregate.
			/// </summary>
			/// <param name="actor">The actor that should be added to the aggregate return true if success.</param>
			bool AddActor(Actor^ actor);

			/// <summary>
			/// Removes an actor from the aggregate object.
			/// A warning is output if the incoming actor does not belong to the aggregate.
			/// Otherwise the actor is removed from the aggregate. If the aggregate belongs to a scene,
			/// the actor is reinserted in that scene. If you intend to delete the actor, it is best
			/// to call PxActor::release() directly. That way the actor will be automatically removed from
			/// its aggregate (if any) and not reinserted in a scene.
			/// </summary>
			/// <param name="actor">The actor that should be removed from the aggregate return true if success.</param>
			bool RemoveActor(Actor^ actor);

			/// <summary>
			/// Adds an articulation to the aggregate object.
			/// A warning is output if the total number of actors is reached (every articulation link counts as an actor),
			/// or if the incoming articulation already belongs to an aggregate.
			/// If the aggregate belongs to a scene, adding an articulation to the aggregate also adds the articulation to that scene.
			/// If the articulation already belongs to a scene, a warning is output and the call is ignored. You need to remove the
			/// articulation from the scene first, before adding it to the aggregate.
			/// </summary>
			/// <param name="articulation">The articulation that should be added to the aggregate return true if success.</param>
			bool AddArticulation(Articulation^ articulation);

			/// <summary>
			/// Removes an articulation from the aggregate object.
			/// A warning is output if the incoming articulation does not belong to the aggregate. Otherwise the articulation
			/// is removed from the aggregate. If the aggregate belongs to a scene, the articulation is reinserted in that scene.
			/// If you intend to delete the articulation, it is best to call PxArticulation::release() directly. That way the
			/// articulation will be automatically removed from its aggregate (if any) and not reinserted in a scene.
			/// </summary>
			/// <param name="articulation">The articulation that should be removed from the aggregate return true if success.</param>
			bool RemoveArticulation(Articulation^ articulation);

			/// <summary>Retrieves a given actor contained in the aggregate.</summary>
			Actor^ GetActor(int index);

			/// <summary>
			/// Gets all the actors in the aggregate.
			/// </summary>
			array<Actor^>^ GetActors();

			/// <summary>
			/// Gets an object which is responsible for serialization of this type.
			/// </summary>
			virtual Serializable^ AsSerializable();

			//

			/// <summary>
			/// Gets the scene which this aggregate belongs to.
			/// </summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Gets the max amount of actors that can be contained in the aggregate.
			/// </summary>
			property int MaximumNumberOfActors
			{
				int get();
			}

			/// <summary>
			/// Gets the current number of actors contained in the aggregate.
			/// </summary>
			property int NumberOfActors
			{
				int get();
			}

			/// <summary>Gets the aggregate's self-collision flag.</summary>
			property bool SelfCollision
			{
				bool get();
			}

		internal:
			property PxAggregate* UnmanagedPointer
			{
				PxAggregate* get();
			}
	};
};