#pragma once

namespace PhysX
{
	ref class Physics;
	ref class Scene;

	/// <summary>
	/// Collection class for serialization.
	/// A collection is a container for serializable SDK objects.
	/// All serializable SDK objects inherit from PxSerializable. Serialization and deserialization only work through collections.
	/// </summary>
	public ref class Collection : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxCollection* _collection;

	internal:
		Collection(PxCollection* collection, IDisposable^ owner);
	public:
		~Collection();
	protected:
		!Collection();
	public:
		property bool Disposed
		{
			virtual bool get();
		}

		[Obsolete]
		void Add(IPhysXEntity^ object);
		void AddId(IPhysXEntity^ object, long reference);

		[Obsolete]
		bool Contains(IPhysXEntity^ object);

		IPhysXEntity^ GetObject(int index);

		void Remove(IPhysXEntity^ object);
		void RemoveId(long reference);

		/// <summary>
		/// Gets number of objects in the collection.
		/// </summary>
		property int NumberOfObjects
		{
			int get();
		}

		property int NumberOfIds
		{
			int get();
		}

	internal:
		property PxCollection* UnmanagedPointer
		{
			PxCollection* get();
		}
	};
};