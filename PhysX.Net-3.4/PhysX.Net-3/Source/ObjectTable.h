#pragma once

#include "IDisposable.h"
#include "ObjectTableOwnershipType.h"
#include "ObjectTableEventArgs.h"

namespace PhysX
{
	ref class ObjectTableEventArgs;
	
	/// <summary>
	/// Manages lookups and disposals for unmanaged-managed pairs.
	/// This class is not thread safe.
	/// </summary>
	public ref class ObjectTable sealed
	{
		public:
			event EventHandler<ObjectTableEventArgs^>^ ObjectAdded;
			event EventHandler<ObjectTableEventArgs^>^ ObjectRemoved;
			
		private:
			static ObjectTable^ _instance;

			// A collection of native objects to their managed version
			Dictionary<intptr_t, Object^>^ _objectTable;
			// A collection of managed objects to their managed owner
			Dictionary<IDisposable^, IDisposable^>^ _ownership;
			// A collection of ownership-type pairs to a collection of objects
			// This dictionary is used to lookup objects which are owned by X and of type Y. (e.g. property Physics.Cloths > Key: Owner: physics, Type: Cloth yields a collection of Cloth).
			Dictionary<ObjectTableOwnershipType, List<Object^>^>^ _ownerTypeLookup;
			
			bool _performingDisposal;
			
	public:
		static ObjectTable()
		{
			_instance = gcnew ObjectTable();
		}

		private:
			ObjectTable();
			
		public:
			void Add(intptr_t pointer, IDisposable^ object, IDisposable^ owner);
			void EnsureUnmanagedObjectIsOnlyWrappedOnce(intptr_t unmanaged, Type^ managedType);
			
			void AddObjectOwner(IDisposable^ object, IDisposable^ owner);
			void AddOwnerTypeLookup(Object^ owner, IDisposable^ object);

			bool Remove(intptr_t pointer);
			bool Remove(Object^ object);
				
			void Clear();
			
			generic<typename T>
			T GetObject(intptr_t pointer);

			generic<typename T>
			T TryGetObject(intptr_t pointer);

			intptr_t GetObject(Object^ object);

			generic<typename T>
			array<T>^ GetObjects(intptr_t* pointers, int count);
			
			generic<typename T> where T : ref class
			array<T>^ GetObjectsOfType();

			generic<typename T> where T : ref class
			array<T>^ GetObjectsOfOwnerAndType(Object^ owner);

			bool Contains(intptr_t pointer);
			bool Contains(Object^ object);
			
		private:
			void disposableObject_OnDisposing(Object^ sender, EventArgs^ e);

			void DisposeOfObjectAndDependents(IDisposable^ disposable);

			array<IDisposable^>^ GetDependents(IDisposable^ disposable);
			void GetDependents(IDisposable^ disposable, List<IDisposable^>^ disposables);
			
		public:
			property int Count
			{
				int get();
			}

			property Dictionary<intptr_t, Object^>^ Objects
			{
				Dictionary<intptr_t, Object^>^ get();
			}
			property Dictionary<IDisposable^, IDisposable^>^ Ownership
			{
				Dictionary<IDisposable^, IDisposable^>^ get();
			}
			property Dictionary<ObjectTableOwnershipType, List<Object^>^>^ OwnerTypeLookup
			{
				Dictionary<ObjectTableOwnershipType, List<Object^>^>^ get();
			}

			property ObjectTable^ Instance
			{
				static ObjectTable^ get();
			}
	};
};