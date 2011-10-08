#pragma once

#include <PxActor.h>
#include "ActorEnum.h"
#include "Bounds3.h"
#include "IObservable.h"

namespace PhysX
{
	ref class Shape;
	ref class Physics;

	/// <summary>
	/// Actor is the base class for the main simulation objects in the physics SDK. 
	///	The actor is owned by and contained in a <see cref="Scene" />.
	/// See <see cref="ActorDesc" /> for a more detailed description of the parameters which can be set when creating an actor.
	/// </summary>
	public ref class Actor abstract : IDisposable, IObservable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxActor* _actor;
			PhysX::Physics^ _physics;

		protected:
			Actor(PxActor* actor, PhysX::Physics^ owner);
		public:
			~Actor();
		protected:
			!Actor();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			virtual ObservableInstance^ GetObservableInstance();

			//

			/// <summary>
			/// Gets the parent physics object.
			/// </summary>
			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}

			/// <summary>
			/// Retrieves the type of actor.
			/// </summary>
			property ActorType Type
			{
				ActorType get();
			}

			/// <summary>
			/// Retrieves the axis aligned bounding box enclosing the actor.
			/// </summary>
			property Bounds3 WorldBounds
			{
				Bounds3 get();
			}

			/// <summary>
			/// Reads the PxActor flags.
			/// </summary>
			property ActorFlag Flags
			{
				ActorFlag get();
				void set(ActorFlag value);
			}

			/// <summary>Gets or sets an object, usually to create a 1:1 relationship with a user object.</summary>
			property Object^ UserData;

		internal:
			property PxActor* UnmanagedPointer
			{
				PxActor* get();
			}
	};
};