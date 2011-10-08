#pragma once

using namespace System::IO;

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
			PhysX::Physics^ _physics;

		internal:
			Collection(PxCollection* collection, PhysX::Physics^ owner);
		public:
			~Collection();
		protected:
			!Collection();
		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Serializes a collection.
			/// Writes out collected objects to a binary stream. Objects are output in the order defined
			/// by PxSerialOrder, according to their type.
			/// "Export names" and "import names", as defined by the setUserData and addExternalRef functions, are also serialized.
			/// </summary>
			void Serialize(System::IO::Stream^ stream);

			/// <summary>
			/// Deserializes a collection.
			/// Initializes/creates objects within the given input buffer, which must have been deserialized from disk
			/// already by the user. The input buffer must be 16-bytes aligned.
			/// Deserialized objects are added to the collection.
			/// Export names for the collection can be retrieved, if necessary. Import names from another collection
			/// can be passed, if necesary.
			/// </summary>
			/// <param name="stream">Deserialized input buffer, 16-bytes aligned.</stream>
			bool Deserialize(System::IO::Stream^ stream);

			/// <summary>Gets number of objects in the collection.</summary>
			int GetNumberOfObjects();

			//

			void CollectPhysicsForExport(PhysX::Physics^ physics);
			void CollectSceneForExport(Scene^ scene);

			//

			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}

		internal:
			property PxCollection* UnmanagedPointer
			{
				PxCollection* get();
			}
	};
};