#pragma once

#include "ActorEnum.h"
#include "Bounds3.h"
#include "ISerializable.h"
#include "Serializable.h"
#include "FoundationEnum.h"
#include "IPhysXEntity.h"

namespace PhysX
{
	ref class Shape;
	ref class Scene;
	ref class Physics;

	/// <summary>
	/// Actor is the base class for the main simulation objects in the physics SDK. 
	///	The actor is owned by and contained in a <see cref="Scene" />.
	/// See <see cref="ActorDesc" /> for a more detailed description of the parameters which can be set when creating an actor.
	/// </summary>
	public ref class Actor abstract : IDisposable, ISerializable, IPhysXEntity
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxActor* _actor;

		protected:
			Actor(PxActor* actor, PhysX::IDisposable^ owner);
		public:
			~Actor();
		protected:
			!Actor();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Retrieves the axis aligned bounding box enclosing the actor.
			/// </summary>
			Bounds3 GetWorldBounds();

			virtual String^ ToString() override;

			//

			/// <summary>
			/// Gets the parent physics of the actor.
			/// </summary>
			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}
			/// <summary>
			/// Gets the parent scene of the actor.
			/// </summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Retrieves the type of actor.
			/// </summary>
			property ActorType Type
			{
				ActorType get();
			}

			/// <summary>
			/// Gets or set the name of the actor.
			/// </summary>
			property String^ Name
			{
				String^ get();
				void set(String^ value);
			}

			/// <summary>
			/// Reads the actor flags.
			/// </summary>
			property ActorFlag Flags
			{
				ActorFlag get();
				void set(ActorFlag value);
			}

			/// <summary>
			/// Assigns dynamic actors a dominance group identifier.
			/// Dominance group is a 5 bit group identifier (legal range from 0 to 31).
			/// </summary>
			/// <remarks>Changing the dominance group does NOT wake the actor up automatically.</remarks>
			property int DominanceGroup
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Gets or sets the owner client of an actor.
			/// This cannot be done once the actor has been placed into a scene.
			/// </summary>
			property int OwnerClient
			{
				int get();
				void set(int value);
			}

			/// <summary>Gets or sets an object, usually to create a 1:1 relationship with a user object.</summary>
			property Object^ UserData;

			virtual Serializable^ AsSerializable();

		internal:
			property PxActor* UnmanagedPointer
			{
				PxActor* get();
			}

			property bool UnmanagedOwner;
	};
};